#include "WIFISocketButton.h"
WIFISocketButtonClass WIFISocketButton;
WIFISocketButtonClass::WIFISocketButtonClass()
{
  this->pin = BUTTON_PIN;
}
void WIFISocketButtonClass::begin(int pin)
{
  this->pin = pin;
  pinMode(this->pin, INPUT);
}
BUTTON_STATE WIFISocketButtonClass::Scan()
{
  const int LONG_PRESS_TIME = 2000;
  const int LONG_PRESS_SETP = 100;
  int       TimeOutCount = 0;
  if (digitalRead(this->pin) == HIGH)
  {
    return NONE_PRESS;
  } else
  {
    delay(10);
    if (digitalRead(this->pin) == HIGH)
    {
      return SHORT_PRESS;
    } else
    {
      for (TimeOutCount = 0; TimeOutCount < LONG_PRESS_TIME; TimeOutCount += LONG_PRESS_SETP)
      {
        if (digitalRead(this->pin) == HIGH)
        {
          break;
        }
        delay(LONG_PRESS_SETP);
      }
      if (TimeOutCount < LONG_PRESS_TIME)
      {
        return SHORT_PRESS;
      } else
      {
        return LONG_PRESS;
      }
    }
  }
}
