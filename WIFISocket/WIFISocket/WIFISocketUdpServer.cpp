#include "WIFISocketUdpServer.h"
#include "WIFISocketCommonService.h"

WIFISocketUdpServerClass::WIFISocketUdpServerClass()
{
  this->port = UDPSERVER_PORT;
}
void WIFISocketUdpServerClass::begin(int port)
{
	this->port = port;
	udp.begin(port);
}
void WIFISocketUdpServerClass::loop()
{
	memset(mPacket, 0, CONFIG_FILE_MAXSIZE);
	if (!udp.parsePacket())
	{
		return;
	}
	udp.read(mPacket, CONFIG_FILE_MAXSIZE);
	/*TODO: Message Process*/
	size_t totalsize=WIFISocketCommonService.Service(mPacket);
	udp.beginPacket(udp.remoteIP(), udp.remotePort());
	udp.write(mPacket, totalsize);
	udp.endPacket();
}

WIFISocketUdpServerClass WIFISocketUdpServer;
