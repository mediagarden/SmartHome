#include "WIFISocketCommon.h"
#include "WIFISocketDebug.h"
#include "WIFISocketFsTools.h"

#include "WIFISocketSwitch.h"
#include "WIFISocketLED.h"
#include "WIFISocketButton.h"
#include "WIFISocketRTCDevice.h"

#include "WIFISocketCommonSettings.h"
#include "WIFISocketCountDownSettings.h"
#include "WIFISocketDeviceSettings.h"
#include "WIFISocketSwitchStateSettings.h"
#include "WIFISocketTimingSettings.h"
#include "WIFISocketRecoverySettings.h"

#include "WIFISocketCountDownTask.h"
#include "WIFISocketDeviceTask.h"
#include "WIFISocketSwitchStateTask.h"
#include "WIFISocketTimingTask.h"

#include "WIFISocketUdpDiscovery.h"
#include "WIFISocketUdpServer.h"


void setup() {
	Serial.begin(115200);
	WIFISocketDebug.begin(DEBUG);
	WIFISocketDebug.Debug("WIFISocket: System on Start!");

	WIFISocketLED.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketLED Inited!");
	WIFISocketSwitch.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketSwitch Inited!");
	WIFISocketButton.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketButton Inited!");
	WIFISocketRTCDevice.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketRTCDevice Inited!");

	
	WIFISocketDeviceSettings.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketDeviceSettings Inited!");
	WIFISocketSwitchStateSettings.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketSwitchStateSettings Inited!");
	WIFISocketCountDownSettings.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketCountDownSettings Inited!");
	WIFISocketTimingSettings.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketTimingSettings Inited!");

	WIFISocketDeviceTask.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketDeviceTask Inited!");
	WIFISocketSwitchStateTask.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketSwitchStateTask Inited!");
	WIFISocketTimingTask.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketTimingTask Inited!");
	WIFISocketCountDownTask.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketCountDownTask Inited!");

	WIFISocketUdpServer.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketUdpServer Inited!");
	WIFISocketUdpDiscovery.begin();
	WIFISocketDebug.Debug("WIFISocket: WIFISocketUdpDiscovery Inited!");
	WIFISocketDebug.Debug("WIFISocket: System Started!");
}

void loop() {

	WIFISocketRTCDevice.loop();
	WIFISocketUdpServer.loop();
	WIFISocketUdpDiscovery.loop();

	WIFISocketDeviceTask.loop();
	WIFISocketSwitchStateTask.loop();
	WIFISocketTimingTask.loop();
	WIFISocketCountDownTask.loop();

	int n = WiFi.scanNetworks();
	Serial.println("scan done");
	if (n == 0)
		Serial.println("no networks found");
	else
	{
		Serial.print(n);
		Serial.println(" networks found");
		for (int i = 0; i < n; ++i)
		{
			// Print SSID and RSSI for each network found
			Serial.print(i + 1);
			Serial.print(": ");
			Serial.print(WiFi.SSID(i));
			Serial.print(" (");
			Serial.print(WiFi.RSSI(i));
			Serial.print(")");
			Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*");
			delay(10);
		}
	}
	Serial.println("");
}
