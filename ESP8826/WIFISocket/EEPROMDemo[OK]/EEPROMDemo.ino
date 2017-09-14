/**
   EEPROM库函数
   JINZHU
   20170902
*/
#include <EEPROM.h>
void setup() {
  EEPROM.begin(512);
  Serial.begin(9600);
  Serial.println("EEPROM");
}

void loop() {
  if (!(EEPROM.read(0x00) == 0xAA && EEPROM.read(0x01) == 0xEE))
  {
    EEPROM.write(0x00, 0xAA);
    EEPROM.write(0x01, 0xEE);
    EEPROM.commit();
    Serial.println("EEPROM Init ...");
  } else
  {
    Serial.println("EEPROM Inited ...");
  }
  delay(3000);
}
