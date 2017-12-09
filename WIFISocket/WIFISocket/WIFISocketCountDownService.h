#ifndef __WIFISOCKETCOUNTDOWNSERVICE_H__
#define __WIFISOCKETCOUNTDOWNSERVICE_H__
#include <Arduino.h>
#include "WIFISocketCommon.h"

class WIFISocketCountDownServiceClass
{
 public:
	 WIFISocketCountDownServiceClass();
	 size_t GetCountDownTask(char packet[]);
	 size_t SetCountDownTask(char packet[]);
};

extern WIFISocketCountDownServiceClass WIFISocketCountDownService;

#endif

