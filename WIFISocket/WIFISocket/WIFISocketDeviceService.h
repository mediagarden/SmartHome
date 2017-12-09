#ifndef __WIFISOCKETDEVICESERVICE_H__
#define __WIFISOCKETDEVICESERVICE_H__
#include <Arduino.h>
#include "WIFISocketCommon.h"
class WIFISocketDeviceServiceClass
{
 public:
	 WIFISocketDeviceServiceClass();
	 size_t GetDevceList(char packet[]);
	 size_t SetRouterSettings(char packet[]);
	 size_t SetAPSettings(char packet[]);
	 size_t SetDeviceName(char packet[]);
	 size_t SetCurrentTime(char packet[]);
};
extern WIFISocketDeviceServiceClass WIFISocketDeviceService;
#endif

