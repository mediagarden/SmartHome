#ifndef __WIFISOCKETSWITCH_H__
#define __WIFISOCKETSWITCH_H__
/*JinZhu 17/9/22 Review */
#include <Arduino.h>
#define SWITCH_PIN	5
class WIFISocketSwitchClass
{
  public:
    WIFISocketSwitchClass();
    void begin(int pin = SWITCH_PIN);
    void Switch(bool state);
    bool getState();
  private:
    int 		pin;
	bool		state;
};
extern WIFISocketSwitchClass WIFISocketSwitch;
#endif
