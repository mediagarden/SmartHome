#include "WIFISocketDebug.h"
#include "WIFISocketRTCDevice.h"
#include "WIFISocketCountDownTask.h"
#include "WIFISocketCountDownService.h"
#include "WIFISocketCountDownSettings.h"

WIFISocketCountDownServiceClass::WIFISocketCountDownServiceClass()
{
}
size_t WIFISocketCountDownServiceClass::GetCountDownTask(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:GetCountDownTask");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& countDown= WIFISocketCountDownSettings.getSettings();
	countDown.remove("TimeStamp");
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	json["CountDownTask"] = countDown;
	int totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}

size_t WIFISocketCountDownServiceClass::SetCountDownTask(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:DeleteCountDownTask");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	JsonObject& countDown = request["CountDownTask"];
	countDown["TimeStamp"] = WIFISocketRTCDevice.getCurrentTime().unixtime();

	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = countDown.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketCountDownSettings.saveSettings(buffer, totalsize);
	delete[] buffer;

	/*TODO:应用改设置*/
	WIFISocketCountDownTask.updateSettings();

	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
WIFISocketCountDownServiceClass WIFISocketCountDownService;

