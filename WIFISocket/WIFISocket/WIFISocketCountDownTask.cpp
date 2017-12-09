#include "WIFISocketSwitch.h"
#include "WIFISocketRTCDevice.h"
#include "WIFISocketCountDownTask.h"
#include "WIFISocketCountDownSettings.h"
WIFISocketCountDownTaskClass::WIFISocketCountDownTaskClass()
{
}
void WIFISocketCountDownTaskClass::begin()
{
}
void WIFISocketCountDownTaskClass::loop()
{
	JsonObject& countDown = WIFISocketCountDownSettings.getSettings();
	if ((bool)countDown["Running"] && WIFISocketRTCDevice.isAvailable())
	{
		bool needSave = false;
		DateTime now = WIFISocketRTCDevice.getCurrentTime();
		DateTime timeStamp = DateTime((uint32_t)countDown["TimeStamp"]);
		uint32_t minutes = (uint32_t)countDown["Minutes"];

		if (now < timeStamp)
		{	/*非法时间*/
			countDown["Running"] = false;
			needSave = true;
		}
		else
		{
			if ((now - timeStamp).totalseconds()>=60)
			{
				uint32_t subMinutes = (now - timeStamp).totalseconds() / 60;
				minutes -= subMinutes;
				timeStamp=timeStamp + TimeDelta(subMinutes * 60);
				countDown["TimeStamp"] = timeStamp.unixtime();
				countDown["Minutes"] = minutes;
				needSave = true;
			}
			if (minutes <= 0)
			{
				bool switchstate = (bool)countDown["SwitchState"];
				/*TODO:应用改设置*/
				WIFISocketSwitch.Switch(switchstate);
				/*TODO:应用改设置*/
				countDown["Running"] = false;
				needSave = true;
			}
		}
		if (needSave)
		{
			char* buffer = new char[PACKET_BUFFER_MAXSIZE];
			int totalsize = countDown.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
			WIFISocketCountDownSettings.saveSettings(buffer, totalsize);
			delete[] buffer;
		}
	}
}
void WIFISocketCountDownTaskClass::updateSettings()
{
}
WIFISocketCountDownTaskClass WIFISocketCountDownTask;

