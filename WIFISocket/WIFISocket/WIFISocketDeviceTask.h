#ifndef __WIFISOCKETDEVICETASK_H__
#define __WIFISOCKETDEVICETASK_H__
#include "WIFISocketCommon.h"
#include <Arduino.h>
#include <ArduinoJson.h>
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>
class WIFISocketDeviceTaskClass
{
public:
	 WIFISocketDeviceTaskClass();
	 void begin();
	 void loop();
	 void updateSettings();
private:
	bool mRouterInited;
	ESP8266WiFiMulti WiFiMulti;
};
extern WIFISocketDeviceTaskClass WIFISocketDeviceTask;
#endif

