#include "WIFISocketDebug.h"
#include "WIFISocketRTCDevice.h"
#include "WIFISocketDeviceTask.h"
#include "WIFISocketDeviceService.h"
#include "WIFISocketDeviceSettings.h"
#include "WIFISocketCommonService.h"


WIFISocketDeviceServiceClass::WIFISocketDeviceServiceClass()
{
}

size_t WIFISocketDeviceServiceClass::GetDevceList(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:GetDevceList");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& device=WIFISocketDeviceSettings.getSettings();
	device["Settings"]["RouterSettings"].asObject().remove("Password");
	device["Settings"]["APSettings"].asObject().remove("Password");
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	json["Device"] = device;
	int totalsize=json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}

size_t WIFISocketDeviceServiceClass::SetRouterSettings(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetRouterSettings");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	String ap = (const char *)request["Name"];
	String password = (const char *)request["Password"];

	JsonObject& deviceJson = WIFISocketDeviceSettings.getSettings();
	deviceJson["Settings"]["RouterSettings"]["AP"] = ap;
	deviceJson["Settings"]["RouterSettings"]["Password"] = password;
	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = deviceJson.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketDeviceSettings.saveSettings(buffer, totalsize);
	delete[] buffer;

	/*TODO:应用设置*/
	WIFISocketDeviceTask.updateSettings();
	/*TODO:应用设置*/

	mServiceJsonBuffer->clear();
	JsonObject& json =mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize=json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}

size_t WIFISocketDeviceServiceClass::SetAPSettings(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetAPSettings");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	String ap = (const char *)request["Name"];
	String password = (const char *)request["Password"];

	JsonObject& deviceJson = WIFISocketDeviceSettings.getSettings();
	deviceJson["Settings"]["APSettings"]["AP"] = ap;
	deviceJson["Settings"]["APSettings"]["Password"] = password;
	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = deviceJson.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketDeviceSettings.saveSettings(buffer, totalsize);
	delete[] buffer;
	/*TODO:应用设置*/
	WIFISocketDeviceTask.updateSettings();
	/*TODO:应用设置*/
	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize=json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;

	return totalsize;
}

size_t WIFISocketDeviceServiceClass::SetDeviceName(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetDeviceName");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	String deviceName = (const char *)request["Name"];

	JsonObject& deviceJson = WIFISocketDeviceSettings.getSettings();
	deviceJson["Name"] = deviceName;
	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = deviceJson.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketDeviceSettings.saveSettings(buffer, totalsize);
	delete[] buffer;

	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize=json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}

size_t WIFISocketDeviceServiceClass::SetCurrentTime(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetCurrentTime");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	uint32_t timeStamp = (uint32_t)request["TimeStamp"];

	WIFISocketRTCDevice.setCurrentTime(DateTime(timeStamp));

	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	int totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
WIFISocketDeviceServiceClass WIFISocketDeviceService;

