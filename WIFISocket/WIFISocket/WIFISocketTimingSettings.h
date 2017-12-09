#ifndef __WIFISOCKETTIMINGSETTINGS_H__
#define __WIFISOCKETTIMINGSETTINGS_H__
#include "WIFISocketCommonSettings.h"
class WIFISocketTimingSettingsClass :public WIFISocketCommonSettingsClass
{
public:
	 WIFISocketTimingSettingsClass();
	void begin();
	JsonObject&	getSettings();
	void saveSettings(char data[], size_t len);
private:
	char	mFileCache[TIMING_CONFIG_FILE_MAXSIZE];
	size_t	mFileCacheLen;
	const char* datafile = "/data/config/Timing.json";
	const char* recoveryfile = "/data/backup/Timing.json";
};

extern WIFISocketTimingSettingsClass WIFISocketTimingSettings;
#endif

