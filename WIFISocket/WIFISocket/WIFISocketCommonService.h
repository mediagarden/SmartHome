#ifndef __WIFISOCKETCOMMONSERVICE_H__
#define __WIFISOCKETCOMMONSERVICE_H__
#include <Arduino.h>
#include <ArduinoJson.h>
#include "WIFISocketCommon.h"
class WIFISocketCommonServiceClass
{
 public:
	 WIFISocketCommonServiceClass();
	 size_t Service(char packet[]);
	 size_t ResponseUnSuccessful(char packet[], String msg);
};
extern WIFISocketCommonServiceClass WIFISocketCommonService;

#endif

