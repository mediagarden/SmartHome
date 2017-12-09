#include <Arduino.h>
#include <ESP8266WiFi.h>
#include "WIFISocketLED.h"
#include "WIFISocketButton.h"
#include "WIFISocketSwitch.h"
#include "WIFISocketDebug.h"
#include "WIFISocketSwitchStateTask.h"
#include "WIFISocketSwitchStateSettings.h"
#include "WIFISocketRecoverySettings.h"
WIFISocketSwitchStateTaskClass::WIFISocketSwitchStateTaskClass()
{
}
void WIFISocketSwitchStateTaskClass::begin()
{
}
void WIFISocketSwitchStateTaskClass::loop()
{
	BUTTON_STATE ButtonState = WIFISocketButton.Scan();
	if (ButtonState == SHORT_PRESS)
	{
		WIFISocketDebug.Debug("WIFISocket:Button Short Pressed...");
		JsonObject& switchstateJson = WIFISocketSwitchStateSettings.getSettings();
		bool switchstate = !((bool)switchstateJson["SwitchState"]);
		WIFISocketSwitch.Switch(switchstate);
		switchstateJson["SwitchState"] = switchstate;
		char* buffer = new char[SWITCHSTATE_CONFIG_FILE_MAXSIZE];
		int totalsize = switchstateJson.prettyPrintTo(buffer, SWITCHSTATE_CONFIG_FILE_MAXSIZE);
		WIFISocketSwitchStateSettings.saveSettings(buffer, totalsize);
		delete[] buffer;
	}
	else if (ButtonState == LONG_PRESS)
	{
		WIFISocketDebug.Debug("WIFISocket:Button Long Pressed...");
		WIFISocketLED.BlinkDelay(500, 3);
		WIFISocketDebug.Debug("WIFISocket:Recovery...");
		WIFISocketRecoverySettings.Recovery();
		WIFISocketLED.BlinkDelay(500, 2);
		WIFISocketDebug.Debug("WIFISocket:Restart...");
		ESP.restart();
	}
}

WIFISocketSwitchStateTaskClass WIFISocketSwitchStateTask;

