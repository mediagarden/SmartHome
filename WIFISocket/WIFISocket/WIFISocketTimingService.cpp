#include "WIFISocketDebug.h"
#include "WIFISocketTimingTask.h"
#include "WIFISocketTimingService.h"
#include "WIFISocketTimingSettings.h"
WIFISocketTimingServiceClass::WIFISocketTimingServiceClass()
{
}
size_t WIFISocketTimingServiceClass::GetTimingTaskList(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:GetTimingTaskList");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& json = WIFISocketTimingSettings.getSettings();
	json["Status"] = 200;
	int totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
size_t WIFISocketTimingServiceClass::SetTimingTaskItem(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetTimingTaskItem");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	JsonObject& timingTask = request["TimingTask"];
	int id = (int)timingTask["Id"];

	JsonObject& timingTaskList = WIFISocketTimingSettings.getSettings();
	timingTaskList["TimingTaskList"].asArray()[id] = timingTask;

	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = timingTaskList.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketTimingSettings.saveSettings(buffer, totalsize);
	delete[] buffer;

	/*TODO:应用改设置*/
	WIFISocketTimingTask.updateSettings(id);

	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
WIFISocketTimingServiceClass WIFISocketTimingService;

