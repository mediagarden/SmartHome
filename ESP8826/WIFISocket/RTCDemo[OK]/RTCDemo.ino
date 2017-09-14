/**
   DS1302库函数
   JINZHU
   20170902
*/

#include "RTClib.h"
#include <DS1302.h>
RTC_Millis rtc;
void setup() {
  Serial.begin(9600);
  Serial.println("RTC_Millis Clock");
  rtc.begin(DateTime(__DATE__, __TIME__));
}

void loop() {
  DateTime now = rtc.now();
  Serial.print(now.year(), DEC);
  Serial.print('/');
  Serial.print(now.month(), DEC);
  Serial.print('/');
  Serial.print(now.day(), DEC);
  Serial.print(' ');
  Serial.print(now.hour(), DEC);
  Serial.print(':');
  Serial.print(now.minute(), DEC);
  Serial.print(':');
  Serial.print(now.second(), DEC);
  Serial.println();
  delay(3000);
}
