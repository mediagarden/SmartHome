#include <Arduino.h>
#include <FS.h>
#include "WIFISocketCommon.h"
#include "WIFISocketFsTools.h"
#include "WIFISocketDebug.h"
#include "WIFISocketTimingSettings.h"
WIFISocketTimingSettingsClass::WIFISocketTimingSettingsClass()
{
}

void WIFISocketTimingSettingsClass::begin()
{
	SPIFFS.begin();
	if (!SPIFFS.exists(datafile))
	{
		WIFISocketFsTools.CopyFile(datafile, recoveryfile);
	}
	SPIFFS.end();
	mFileCacheLen = WIFISocketFsTools.ReadFile(datafile, mFileCache, TIMING_CONFIG_FILE_MAXSIZE);
}

JsonObject&	WIFISocketTimingSettingsClass::getSettings()
{
	memcpy(mCommonFileBuffer, mFileCache, TIMING_CONFIG_FILE_MAXSIZE);
	mCommonJsonBuffer.clear();
	return mCommonJsonBuffer.parseObject(mCommonFileBuffer);
}

void WIFISocketTimingSettingsClass::saveSettings(char data[], size_t len)
{
	memset(mFileCache, 0, TIMING_CONFIG_FILE_MAXSIZE);
	memcpy(mFileCache, data, len);
	WIFISocketFsTools.WriteFile(datafile, mFileCache, len);
}

WIFISocketTimingSettingsClass WIFISocketTimingSettings;

