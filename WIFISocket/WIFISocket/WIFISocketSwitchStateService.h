#ifndef __WIFISOCKETSWITCHSTATESERVICE_H__
#define __WIFISOCKETSWITCHSTATESERVICE_H__
#include <Arduino.h>
#include "WIFISocketCommon.h"
class WIFISocketSwitchStateServiceClass
{
 public:
	 WIFISocketSwitchStateServiceClass();
	 size_t GetSwitchState(char packet[]);
	 size_t SetSwitchState(char packet[]);
};

extern WIFISocketSwitchStateServiceClass WIFISocketSwitchStateService;

#endif

