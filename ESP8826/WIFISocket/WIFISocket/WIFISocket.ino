#include <DS1302.h>
DS1302 rtc(13, 12, 14);
void setup() {
  // put your setup code here, to run once:
  rtc.halt(false);
  rtc.writeProtect(false);
  Serial.begin(9600);
}

void loop() {
  // Send Day-of-Week
  Serial.print(rtc.getDOWStr());
  Serial.print(" ");
  // Send date
  Serial.print(rtc.getDateStr());
  Serial.print(" -- ");

  // Send time
  Serial.println(rtc.getTimeStr());

  // Wait one second before repeating :)
  delay (1000);
}
