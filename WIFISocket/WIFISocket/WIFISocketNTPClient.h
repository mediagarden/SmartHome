#ifndef __WIFISOCKETNTPCLIENT_H__
#define __WIFISOCKETNTPCLIENT_H__
#include "RTClib.h"
#include <WiFiUdp.h>
#include <ESP8266WiFi.h>


#define SECONDS_FROM_1900_TO_1970  2208988800UL
#define SECONDS_FROM_UTC_TO_GMT8   28800

#define NTP_PACKET_SIZE				48                  // NTP time stamp is in the first 48 bytes of the message
#define NTP_SERVER_NAME			"ntp1.aliyun.com"
#define LOCAL_PORT						2390                // local port to listen for UDP packets

class WIFISocketNTPClientClass
{
 public:
	 WIFISocketNTPClientClass();
	 bool getDateTime(DateTime& dt);
private:
	unsigned long sendNTPpacket(IPAddress& address);
	IPAddress timeServerIP;                            // time.nist.gov NTP server address
	byte packetBuffer[NTP_PACKET_SIZE];                //buffer to hold incoming and outgoing packets
	WiFiUDP udp;                                        // A UDP instance to let us send and receive packets over UDP
};

extern WIFISocketNTPClientClass WIFISocketNTPClient;

#endif

