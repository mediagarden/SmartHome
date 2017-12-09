#ifndef __WIFISOCKETDEVICESETTINGS_H__
#define __WIFISOCKETDEVICESETTINGS_H__
#include "WIFISocketCommonSettings.h"
class WIFISocketDeviceSettingsClass :public WIFISocketCommonSettingsClass
{
public:
	WIFISocketDeviceSettingsClass();
	void begin();
	JsonObject&	getSettings();
	void saveSettings(char data[], size_t len);
private:
	char	mFileCache[COUNTDOWN_CONFIG_FILE_MAXSIZE];
	size_t	mFileCacheLen;
	const char* datafile = "/config/Device.json";
	const char* recoveryfile = "/backup/Device.json";
};
extern WIFISocketDeviceSettingsClass WIFISocketDeviceSettings;
#endif

