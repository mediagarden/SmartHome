#ifndef __WIFISOCKETLED_H__
#define __WIFISOCKETLED_H__
/*JinZhu 17/9/22 Review */
#include<Arduino.h>
#include <Ticker.h>
#define LED_PIN			LED_BUILTIN
#define BLINK_LED_DELAY	1000

class WIFISocketLEDClass
{
  public:
    WIFISocketLEDClass();
    void begin(int pin = LED_PIN);
    void Blink(int time = BLINK_LED_DELAY);
    void Blink(int time, int count);
    void BlinkDelay(int time = BLINK_LED_DELAY);
    void BlinkDelay(int time, int count);
    void BlinkHandle();
    void Switch(bool state);
    bool getState();
  private:
    Ticker      ticker;
    int         blinkCount;
  private:
    int 	pin;
    bool 	state;
};
extern WIFISocketLEDClass    WIFISocketLED;
#endif
