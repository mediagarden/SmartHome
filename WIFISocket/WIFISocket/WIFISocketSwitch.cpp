#include "WIFISocketSwitch.h"
#include "WIFISocketLED.h"
WIFISocketSwitchClass WIFISocketSwitch;
WIFISocketSwitchClass::WIFISocketSwitchClass()
{
	this->pin = SWITCH_PIN;
}
void WIFISocketSwitchClass::begin(int pin)
{
	this->pin = pin;
	pinMode(this->pin, OUTPUT);
	this->Switch(state);
	WIFISocketLED.Switch(state);
}
void WIFISocketSwitchClass::Switch(bool state)
{
	this->state = state;
	WIFISocketLED.Switch(state);
	if (state)
	{
		digitalWrite(this->pin, HIGH);
	} else
	{
		digitalWrite(this->pin, LOW);
	}
}
bool WIFISocketSwitchClass::getState()
{
	return state;
}
