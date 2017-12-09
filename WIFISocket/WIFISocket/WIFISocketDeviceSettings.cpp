#include <Arduino.h>
#include <FS.h>
#include "WIFISocketCommon.h"
#include "WIFISocketFsTools.h"
#include "WIFISocketDebug.h"
#include "WIFISocketDeviceSettings.h"
WIFISocketDeviceSettingsClass::WIFISocketDeviceSettingsClass()
{
}
void WIFISocketDeviceSettingsClass::begin()
{
	SPIFFS.begin();
	if (!SPIFFS.exists(datafile))
	{
		WIFISocketFsTools.CopyFile(datafile, recoveryfile);
	}
	SPIFFS.end();
	mFileCacheLen = WIFISocketFsTools.ReadFile(datafile, mFileCache, DEVICE_CONFIG_FILE_MAXSIZE);
}

JsonObject&	WIFISocketDeviceSettingsClass::getSettings()
{
	memcpy(mCommonFileBuffer, mFileCache, DEVICE_CONFIG_FILE_MAXSIZE);
	mCommonJsonBuffer.clear();
	return mCommonJsonBuffer.parseObject(mCommonFileBuffer);
}

void WIFISocketDeviceSettingsClass::saveSettings(char data[], size_t len)
{
	memset(mFileCache, 0, DEVICE_CONFIG_FILE_MAXSIZE);
	memcpy(mFileCache, data, len);
	WIFISocketFsTools.WriteFile(datafile, mFileCache, len);
}
WIFISocketDeviceSettingsClass WIFISocketDeviceSettings;

