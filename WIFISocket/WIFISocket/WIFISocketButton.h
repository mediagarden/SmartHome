#ifndef __WIFISOCKETBUTTON_H__
#define __WIFISOCKETBUTTON_H__
/*JinZhu 17/9/22 Review */
#include <Arduino.h>
#define BUTTON_PIN	4
typedef enum BUTTON_STATE
{
  NONE_PRESS = 0,
  SHORT_PRESS = 1,
  LONG_PRESS = 2,
} BUTTON_STATE;
class WIFISocketButtonClass
{
  public:
    WIFISocketButtonClass();
    void begin(int pin = BUTTON_PIN);
    BUTTON_STATE  Scan();
  private:
    int 	pin;
};
extern WIFISocketButtonClass WIFISocketButton;
#endif
