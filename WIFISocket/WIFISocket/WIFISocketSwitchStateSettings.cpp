#include <Arduino.h>
#include <FS.h>
#include "WIFISocketCommon.h"
#include "WIFISocketFsTools.h"
#include "WIFISocketDebug.h"
#include "WIFISocketSwitchStateSettings.h"
WIFISocketSwitchStateSettingsClass::WIFISocketSwitchStateSettingsClass()
{
}

void WIFISocketSwitchStateSettingsClass::begin()
{
	SPIFFS.begin();
	if (!SPIFFS.exists(datafile))
	{
		WIFISocketFsTools.CopyFile(datafile, recoveryfile);
	}
	SPIFFS.end();
	mFileCacheLen = WIFISocketFsTools.ReadFile(datafile, mFileCache, SWITCHSTATE_CONFIG_FILE_MAXSIZE);
}

JsonObject&	WIFISocketSwitchStateSettingsClass::getSettings()
{
	memcpy(mCommonFileBuffer, mFileCache, SWITCHSTATE_CONFIG_FILE_MAXSIZE);
	mCommonJsonBuffer.clear();
	return mCommonJsonBuffer.parseObject(mCommonFileBuffer);
}

void WIFISocketSwitchStateSettingsClass::saveSettings(char data[], size_t len)
{
	memset(mFileCache, 0, SWITCHSTATE_CONFIG_FILE_MAXSIZE);
	memcpy(mFileCache, data, len);
	WIFISocketFsTools.WriteFile(datafile, mFileCache, len);
}

WIFISocketSwitchStateSettingsClass WIFISocketSwitchStateSettings;

