#ifndef _NTPCLIENT_H_
#define _NTPCLIENT_H_
#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include "RTClib.h"

#define SECONDS_FROM_1900_TO_1970  2208988800UL
#define SECONDS_FROM_UTC_TO_GMT8   28800

#define NTP_PACKET_SIZE            48                  // NTP time stamp is in the first 48 bytes of the message
#define NTP_SERVER_NAME            "time.nist.gov"
#define LOCAL_PORT                 2390                // local port to listen for UDP packets
class NTPClient
{
  public:
    NTPClient();
    bool getDateTime(DateTime *dt);
  private:
    unsigned long sendNTPpacket(IPAddress& address);
    IPAddress timeServerIP;                            // time.nist.gov NTP server address
    byte packetBuffer[ NTP_PACKET_SIZE];                //buffer to hold incoming and outgoing packets
    WiFiUDP udp;                                        // A UDP instance to let us send and receive packets over UDP
};

#endif // _NTPCLIENT_H_
