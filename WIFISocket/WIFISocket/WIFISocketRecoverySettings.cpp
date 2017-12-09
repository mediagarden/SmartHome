#include <Arduino.h>
#include <FS.h>
#include <ArduinoJson.h>
#include "WIFISocketDebug.h"
#include "WIFISocketRecoverySettings.h"
////////////////////////////////////////////////////
WIFISocketRecoverySettingsClass::WIFISocketRecoverySettingsClass()
{
}
void WIFISocketRecoverySettingsClass::Recovery()
{
	const int SETTING_COUNT = 4;
	const char* SettngFiles[SETTING_COUNT] = {
		"/config/CountDown.json",
		"/config/Device.json",
		"/config/SwitchState.json",
		"/config/Timing.json",
	};
	WIFISocketDebug.Debug("WIFISocket:Delete The Settings Files...");
	SPIFFS.begin();
	for (int line = 0; line < SETTING_COUNT; line++)
	{
		SPIFFS.remove(SettngFiles[line]);
	}
	SPIFFS.end();
}
WIFISocketRecoverySettingsClass WIFISocketRecoverySettings;