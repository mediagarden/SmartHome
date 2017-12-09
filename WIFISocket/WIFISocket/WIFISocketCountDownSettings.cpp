#include <Arduino.h>
#include <FS.h>
#include "WIFISocketCommon.h"
#include "WIFISocketFsTools.h"
#include "WIFISocketDebug.h"
#include "WIFISocketCountDownSettings.h"
WIFISocketCountDownSettingsClass::WIFISocketCountDownSettingsClass()
{
}
void WIFISocketCountDownSettingsClass::begin()
{
	SPIFFS.begin();
	if (!SPIFFS.exists(datafile))
	{
		WIFISocketFsTools.CopyFile(datafile, recoveryfile);
	}
	SPIFFS.end();
	mFileCacheLen = WIFISocketFsTools.ReadFile(datafile, mFileCache, COUNTDOWN_CONFIG_FILE_MAXSIZE);
}

JsonObject&	WIFISocketCountDownSettingsClass::getSettings()
{
	memcpy(mCommonFileBuffer, mFileCache, COUNTDOWN_CONFIG_FILE_MAXSIZE);
	mCommonJsonBuffer.clear();
	return mCommonJsonBuffer.parseObject(mCommonFileBuffer);
}

void WIFISocketCountDownSettingsClass::saveSettings(char data[], size_t len)
{
	memset(mFileCache, 0, COUNTDOWN_CONFIG_FILE_MAXSIZE);
	memcpy(mFileCache, data, len);
	WIFISocketFsTools.WriteFile(datafile, mFileCache, len);
}

WIFISocketCountDownSettingsClass WIFISocketCountDownSettings;

