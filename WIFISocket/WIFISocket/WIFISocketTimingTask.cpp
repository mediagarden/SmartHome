#include "WIFISocketSwitch.h"
#include "WIFISocketRTCDevice.h"
#include "WIFISocketTimingTask.h"
#include "WIFISocketTimingSettings.h"
WIFISocketTimingTaskClass::WIFISocketTimingTaskClass()
{
}
void WIFISocketTimingTaskClass::begin()
{
}
void WIFISocketTimingTaskClass::loop()
{
	bool needSave = false;
	JsonObject& timing = WIFISocketTimingSettings.getSettings();
	for (int taskId = 1; taskId <= 5; taskId++)
	{
		JsonObject& timingTask = timing["TimingTaskList"].asArray()[taskId - 1];
		if ((bool)timingTask["Running"] && WIFISocketRTCDevice.isAvailable())
		{
			uint8_t loopMark = (uint8_t)timingTask["LoopMark"];
			DateTime now = WIFISocketRTCDevice.getCurrentTime();
			if (loopMark & 0x80)
			{	/*单次定时任务*/
				for (int actionId = 0; actionId < 2; actionId++)
				{
					JsonObject& action = timingTask["Action"].asArray()[actionId];
					if ((bool)action["Available"])
					{
						int timeStamp = (bool)action["TimeStamp"];
						DateTime actionTime(timeStamp);
						if (now.year() == actionTime.year()&&now.month() == actionTime.month() && now.day() == actionTime.day())
						{
							if (now.hour() == actionTime.hour() && now.minute() == actionTime.minute())
							{
								bool switchstate = (bool)action["SwitchState"];
								/*TODO:应用改设置*/
								WIFISocketSwitch.Switch(switchstate);
								/*TODO:应用改设置*/
								action["Available"] = false;
								needSave = true;
							}
						}
					}
				}
				{
					bool IsRunning= false;
					for (int actionId = 0; actionId < 2; actionId++)
					{
						JsonObject& action = timingTask["Action"].asArray()[actionId];
						if ((bool)action["Available"])
						{
							IsRunning = true;
						}
					}
					if (!IsRunning)
					{
						timingTask["Running"] = false;
						needSave = true;
					}
				}
			}
			else
			{	/*循环定时任务*/
				for (int actionId = 0; actionId < 2; actionId++)
				{
					JsonObject& action = timingTask["Action"].asArray()[actionId];
					if ((bool)action["Available"])
					{
						int timeStamp = (bool)action["TimeStamp"];
						DateTime actionTime(timeStamp);
						if ((1<<now.dayOfWeek())&loopMark)
						{
							if (now.hour() == actionTime.hour() && now.minute() == actionTime.minute())
							{
								bool switchstate = (bool)action["SwitchState"];
								/*TODO:应用改设置*/
								WIFISocketSwitch.Switch(switchstate);
								/*TODO:应用改设置*/
							}
						}
					}
				}
			}
		}
	}
	if (needSave)
	{
		char* buffer = new char[PACKET_BUFFER_MAXSIZE];
		int totalsize = timing.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
		WIFISocketTimingSettings.saveSettings(buffer, totalsize);
		delete[] buffer;
	}
}
void WIFISocketTimingTaskClass::updateSettings(int id)
{
}
WIFISocketTimingTaskClass WIFISocketTimingTask;

