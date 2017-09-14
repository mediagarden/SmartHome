/**
   NTP Demo时间同步
   JINZHU
   20170902
*/
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "RTClib.h"
#include "NTPClient.h"

char ssid[] = "Doraemon";
char pass[] = "Doraemon";

RTC_Millis rtc;
void setup() {
  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, pass);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  DateTime now;
  NTPClient ntp;
  if (!ntp.getDateTime(&now))
  {
    Serial.println("Failed to Get Time!");
    delay(3000);
    return;
  }
  Serial.println("Get Time Success!");
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

