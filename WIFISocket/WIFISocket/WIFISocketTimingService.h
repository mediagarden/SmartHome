#ifndef __WIFISOCKETTIMINGSERVICE_H__
#define __WIFISOCKETTIMINGSERVICE_H__
#include <Arduino.h>
#include "WIFISocketCommon.h"
class WIFISocketTimingServiceClass
{
 public:
	 WIFISocketTimingServiceClass();
	 size_t GetTimingTaskList(char packet[]);
	 size_t SetTimingTaskItem(char packet[]);
};

extern WIFISocketTimingServiceClass WIFISocketTimingService;

#endif

