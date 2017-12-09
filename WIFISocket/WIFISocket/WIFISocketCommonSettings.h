#ifndef __WIFISOCKETCOMMONSETTINGS_H__
#define __WIFISOCKETCOMMONSETTINGS_H__
#include <ArduinoJson.h>
#include"WIFISocketCommon.h"
class WIFISocketCommonSettingsClass
{
public:
	virtual void begin()=0;
	virtual JsonObject&	getSettings()=0;
	virtual void saveSettings(char data[], size_t len)=0;
protected:
	static StaticJsonBuffer<CONFIG_FILE_MAXSIZE> mCommonJsonBuffer;
	static char mCommonFileBuffer[CONFIG_FILE_MAXSIZE];
};
#endif

