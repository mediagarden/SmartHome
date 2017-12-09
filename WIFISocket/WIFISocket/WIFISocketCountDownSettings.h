#ifndef __WIFISOCKETCOUNTDOWNSETTINGS_H__
#define __WIFISOCKETCOUNTDOWNSETTINGS_H__
#include "WIFISocketCommonSettings.h"
class WIFISocketCountDownSettingsClass :public WIFISocketCommonSettingsClass
{
public:
	 WIFISocketCountDownSettingsClass();
	 void begin();
	 JsonObject&	getSettings();
	 void saveSettings(char data[], size_t len);
private:
	char	mFileCache[COUNTDOWN_CONFIG_FILE_MAXSIZE];
	size_t	mFileCacheLen;
	const char* datafile = "/config/CountDown.json";
	const char* recoveryfile = "/backup/CountDown.json";
};
extern WIFISocketCountDownSettingsClass WIFISocketCountDownSettings;
#endif

