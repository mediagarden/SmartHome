#include "NTPClient.h"

NTPClient::NTPClient()
{
  udp.begin(LOCAL_PORT);
}

bool NTPClient::getDateTime(DateTime *dt)
{
  int tryTimes = 0;
  int cb = 0;
  WiFi.hostByName(NTP_SERVER_NAME, timeServerIP);
  sendNTPpacket(timeServerIP); // send an NTP packet to a time server
  while (tryTimes < 5 && !cb)
  {
    delay(1000);
    cb = udp.parsePacket();
    tryTimes++;
  }
  if (!cb)
  {
    return false;
  }
  // We've received a packet, read the data from it
  udp.read(packetBuffer, NTP_PACKET_SIZE); // read the packet into the buffer
  //the timestamp starts at byte 40 of the received packet and is four bytes,
  // or two words, long. First, esxtract the two words:
  unsigned long highWord = word(packetBuffer[40], packetBuffer[41]);
  unsigned long lowWord = word(packetBuffer[42], packetBuffer[43]);
  // combine the four bytes (two words) into a long integer
  // this is NTP time (seconds since Jan 1 1900):
  unsigned long secsSince1900 = highWord << 16 | lowWord;
  *dt = DateTime(secsSince1900 - SECONDS_FROM_1900_TO_1970 + SECONDS_FROM_UTC_TO_GMT8);
  return true;
}

// send an NTP request to the time server at the given address
unsigned long NTPClient::sendNTPpacket(IPAddress& address)
{
  // set all bytes in the buffer to 0
  memset(packetBuffer, 0, NTP_PACKET_SIZE);
  // Initialize values needed to form NTP request
  // (see URL above for details on the packets)
  packetBuffer[0] = 0b11100011;   // LI, Version, Mode
  packetBuffer[1] = 0;     // Stratum, or type of clock
  packetBuffer[2] = 6;     // Polling Interval
  packetBuffer[3] = 0xEC;  // Peer Clock Precision
  // 8 bytes of zero for Root Delay & Root Dispersion
  packetBuffer[12]  = 49;
  packetBuffer[13]  = 0x4E;
  packetBuffer[14]  = 49;
  packetBuffer[15]  = 52;
  // all NTP fields have been given values, now
  // you can send a packet requesting a timestamp:
  udp.beginPacket(address, 123); //NTP requests are to port 123
  udp.write(packetBuffer, NTP_PACKET_SIZE);
  udp.endPacket();
}
