#include "WIFISocketDeviceTask.h"
#include "WIFISocketDebug.h"
#include "WIFISocketDeviceSettings.h"
WIFISocketDeviceTaskClass::WIFISocketDeviceTaskClass()
{
	mRouterInited = false;
}
void WIFISocketDeviceTaskClass::begin()
{
		//连接SoftAP并更新DeviceConfig
		WiFi.disconnect();
		WiFi.mode(WIFI_STA);
		JsonObject& deviceJson = WIFISocketDeviceSettings.getSettings();
		WIFISocketDebug.Debug("WIFISocket: Create Soft AP:%s!", (const char *)deviceJson["Settings"]["APSettings"]["AP"]);
		WiFi.softAP((const char *)deviceJson["Settings"]["APSettings"]["AP"], (const char *)deviceJson["Settings"]["APSettings"]["Password"]);
		IPAddress myIP = WiFi.softAPIP();
		deviceJson["Settings"]["APSettings"]["IP"] = myIP.toString();
		WIFISocketDebug.Debug("WIFISocket:IP address on Soft AP:%d.%d.%d.%d!", myIP[0], myIP[1], myIP[2], myIP[3]);

		WIFISocketDebug.Debug("WIFISocket:Connecting to Router:%s!", (const char *)deviceJson["Settings"]["RouterSettings"]["AP"]);
		WiFiMulti.addAP((const char *)deviceJson["Settings"]["RouterSettings"]["AP"], (const char *)deviceJson["Settings"]["RouterSettings"]["Passowrd"]);

		WiFi.setAutoConnect(true);
		WiFi.setAutoReconnect(true);
		int timeout = 30;
		while (!WiFi.isConnected()&&timeout!=0)
		{
			delay(100);
			timeout--;
		}
		if (WiFi.isConnected())
		{
			myIP = WiFi.localIP();
			WIFISocketDebug.Debug("WIFISocket:Connected to Router!");
			WIFISocketDebug.Debug("WIFISocket:IP address on Router:%d.%d.%d.%d!", myIP[0], myIP[1], myIP[2], myIP[3]);
			deviceJson["Settings"]["RouterSettings"]["IP"] = myIP.toString();
			mRouterInited = true;
		}
		char* buffer = new char[CONFIG_FILE_MAXSIZE];
		int totalSize = deviceJson.prettyPrintTo(buffer, CONFIG_FILE_MAXSIZE);
		WIFISocketDeviceSettings.saveSettings(buffer, totalSize);
		delete[] buffer;
}
void WIFISocketDeviceTaskClass::loop()
{
	if (WiFi.isConnected())
	{
		if (!mRouterInited)
		{
			JsonObject& deviceJson = WIFISocketDeviceSettings.getSettings();
			IPAddress myIP = WiFi.localIP();
			WIFISocketDebug.Debug("WIFISocket:Connected to Router");
			WIFISocketDebug.Debug("WIFISocket:IP address on Router:%d.%d.%d.%d", myIP[0], myIP[1], myIP[2], myIP[3]);
			deviceJson["Settings"]["RouterSettings"]["IP"] = myIP.toString();
			mRouterInited = true;
			char* buffer = new char[CONFIG_FILE_MAXSIZE];
			int totalSize = deviceJson.prettyPrintTo(buffer, CONFIG_FILE_MAXSIZE);
			WIFISocketDeviceSettings.saveSettings(buffer, totalSize);
			delete[] buffer;
		}
	}
	else
	{
		mRouterInited = false;
	}
}
void WIFISocketDeviceTaskClass::updateSettings()
{
}
WIFISocketDeviceTaskClass WIFISocketDeviceTask;

