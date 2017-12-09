#ifndef _WIFISOCKETUDPSERVER_H_
#define _WIFISOCKETUDPSERVER_H_
#include <Arduino.h>
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "WIFISocketCommon.h"
#include "WIFISocketDebug.h"
#define UDPSERVER_PORT					10001
class WIFISocketUdpServerClass
{
  public:
    WIFISocketUdpServerClass();
    void begin(int port = UDPSERVER_PORT);
    void loop();
  private:
	char	mPacket[CONFIG_FILE_MAXSIZE];
    WiFiUDP udp;
    int port;
};
extern WIFISocketUdpServerClass WIFISocketUdpServer;
#endif

