#include "WIFISocketLED.h"
#include "WIFISocketButton.h"
#include "WIFISocketSwitch.h"
#include "WIFISocketDebug.h"
#include "WIFISocketSwitchStateSettings.h"
#include "WIFISocketSwitchStateService.h"
#include "WIFISocketCommonService.h"
WIFISocketSwitchStateServiceClass::WIFISocketSwitchStateServiceClass()
{
}
size_t WIFISocketSwitchStateServiceClass::GetSwitchState(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:GetSwitchState");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& switchstateJson = WIFISocketSwitchStateSettings.getSettings();
	bool switchstate =(bool) switchstateJson["SwitchState"];
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	json["SwitchState"] = switchstate;
	int totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
size_t WIFISocketSwitchStateServiceClass::SetSwitchState(char packet[])
{
	WIFISocketDebug.Debug("WIFISocket:SetSwitchState");
	StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>* mServiceJsonBuffer = new StaticJsonBuffer<PACKET_BUFFER_MAXSIZE>();
	JsonObject& request = mServiceJsonBuffer->parseObject(packet);
	bool switchstate = (bool)request["SwitchState"];
	/*TODO:应用改设置*/
	WIFISocketSwitch.Switch(switchstate);
	/*TODO:应用改设置*/
	JsonObject& switchstateJson = WIFISocketSwitchStateSettings.getSettings();
	switchstateJson["SwitchState"] = switchstate;
	char* buffer = new char[PACKET_BUFFER_MAXSIZE];
	int totalsize = switchstateJson.prettyPrintTo(buffer, PACKET_BUFFER_MAXSIZE);
	WIFISocketSwitchStateSettings.saveSettings(buffer, totalsize);
	delete[] buffer;

	mServiceJsonBuffer->clear();
	JsonObject& json = mServiceJsonBuffer->createObject();
	json["Status"] = 200;
	totalsize = json.printTo(packet, PACKET_BUFFER_MAXSIZE);
	delete mServiceJsonBuffer;
	return totalsize;
}
WIFISocketSwitchStateServiceClass WIFISocketSwitchStateService;

