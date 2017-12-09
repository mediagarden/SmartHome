#ifndef __WIFISOCKETSWITCHSTATESETTINGS_H__
#define __WIFISOCKETSWITCHSTATESETTINGS_H__
#include "WIFISocketCommonSettings.h"
class WIFISocketSwitchStateSettingsClass:public WIFISocketCommonSettingsClass
{
public:
	WIFISocketSwitchStateSettingsClass();
	void begin();
	JsonObject&	getSettings();
	void saveSettings(char data[], size_t len);
private:
	char	mFileCache[SWITCHSTATE_CONFIG_FILE_MAXSIZE];
	size_t	mFileCacheLen;
	const char* datafile = "/config/SwitchState.json";
	const char* recoveryfile = "/backup/SwitchState.json";
};

extern WIFISocketSwitchStateSettingsClass WIFISocketSwitchStateSettings;
#endif

