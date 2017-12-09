#include "WIFISocketLED.h"
WIFISocketLEDClass    WIFISocketLED;

static void WIFISocketTickerHandle(WIFISocketLEDClass* WIFISocketLED)
{
  WIFISocketLED->BlinkHandle();
}

WIFISocketLEDClass::WIFISocketLEDClass()
{
  this->pin = LED_PIN;
  this->state = false;
  this->blinkCount = 0;
}
void WIFISocketLEDClass::BlinkHandle()
{
  if (this->blinkCount == 0)
  {
    ticker.detach();
    return;
  }
  this->blinkCount--;
  this->Switch(!this->getState());
}
void WIFISocketLEDClass::Blink(int time)
{
  this->ticker.detach();
  this->blinkCount = (1 * 2) - 1;
  this->ticker.attach_ms(time, WIFISocketTickerHandle, this);
  this->BlinkHandle();
}
void WIFISocketLEDClass::Blink(int time, int count)
{
  this->ticker.detach();
  this->blinkCount = (count * 2) - 1;
  this->ticker.attach_ms(time, WIFISocketTickerHandle, this);
  this->BlinkHandle();
}
void WIFISocketLEDClass::BlinkDelay(int time)
{
  this->Switch(!this->getState());
  delay(time);
  this->Switch(!this->getState());
  delay(time);
}
void WIFISocketLEDClass::BlinkDelay(int time, int count)
{
  for (int i = 0; i < count; i++)
  {
    this->Switch(!this->getState());
    delay(time);
    this->Switch(!this->getState());
    delay(time);
  }
}
void WIFISocketLEDClass::begin(int pin)
{
  this->pin = pin;
  pinMode(this->pin, OUTPUT);
  this->Switch(false);
}
void WIFISocketLEDClass::Switch(bool state)
{
  this->state = state;
  if (state)
  {
    digitalWrite(this->pin, LOW);
  } else
  {
    digitalWrite(this->pin, HIGH);
  }
}
bool WIFISocketLEDClass::getState()
{
  return this->state;
}
