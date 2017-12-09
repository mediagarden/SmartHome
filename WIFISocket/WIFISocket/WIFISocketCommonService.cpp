#include "WIFISocketDebug.h"
#include "WIFISocketCommonService.h"
#include "WIFISocketSwitchStateService.h"
#include "WIFISocketDeviceService.h"
#include "WIFISocketTimingService.h"
#include "WIFISocketCountDownService.h"
WIFISocketCommonServiceClass::WIFISocketCommonServiceClass()
{
}
size_t WIFISocketCommonServiceClass::ResponseUnSuccessful(char packet[],String msg)
{
	WIFISocketDebug.Debug("WIFISocket:ResponseUnSuccessful");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	mServiceJsonBuffer->clear();
	JsonObject& root = mServiceJsonBuffer->createObject();
	root["Status"] =404;
	root["Error"] = msg;
	memset(packet, 0, sizeof(packet));
	size_t totalsize=root.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
size_t WIFISocketCommonServiceClass::Service(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:Service");
	WIFISocketDebug.Debug(packet);

	char* jsonPacket=new char[PACKET_BUFFER_MAXSIZE];
	memcpy(jsonPacket, packet, PACKET_BUFFER_MAXSIZE);

	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& root = mServiceJsonBuffer->parseObject(jsonPacket);
	bool jsonState = root.success();
	String Cmd((const char *)root["Cmd"]);
	delete mServiceJsonBuffer;
	delete[] jsonPacket;

	if (!jsonState)
	{
		return ResponseUnSuccessful(packet, "Parse Object Error.");
	}
	if (Cmd.equals("GetDeviceList"))
	{
		return WIFISocketDeviceService.GetDevceList(packet);
	}
	else if (Cmd.equals("SetRouterSettings"))
	{
		return WIFISocketDeviceService.SetRouterSettings(packet);
	}
	else if (Cmd.equals("SetAPSettings"))
	{
		return WIFISocketDeviceService.SetAPSettings(packet);
	}
	else if (Cmd.equals("SetDeviceName"))
	{
		return WIFISocketDeviceService.SetDeviceName(packet);
	}
	else if (Cmd.equals("SetCurrentTime"))
	{
		return WIFISocketDeviceService.SetCurrentTime(packet);
	}
	else if (Cmd.equals("GetSwitchState"))
	{
		return WIFISocketSwitchStateService.GetSwitchState(packet);
	}
	else if (Cmd.equals("SetSwitchState"))
	{
		return WIFISocketSwitchStateService.SetSwitchState(packet);
	}
	else if (Cmd.equals("GetTimingTaskList"))
	{
		return WIFISocketTimingService.GetTimingTaskList(packet);
	}
	else if (Cmd.equals("SetTimingTaskItem"))
	{
		return WIFISocketTimingService.SetTimingTaskItem(packet);
	}
	else if (Cmd.equals("GetCountDownTask"))
	{
		return WIFISocketCountDownService.GetCountDownTask(packet);
	}
	else if (Cmd.equals("SetCountDownTask"))
	{
		return WIFISocketCountDownService.SetCountDownTask(packet);
	}
	else
	{
		return ResponseUnSuccessful(packet, "Unknown Message.");
	}
}
WIFISocketCommonServiceClass WIFISocketCommonService;


