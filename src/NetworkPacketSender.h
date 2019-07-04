
#ifndef NETWORKPACKETSENDER_H
#define NETWORKPACKETSENDER_H
#include <ctime>
#include <iomanip>
namespace NetworkProtocal
{
enum NetworkProtocal
{
	TCP,
	UDP
};
}

class NetworkPacketSender
{

public:
	virtual ~NetworkPacketSender() = default;
	virtual void InitialiseConnection(const char *IPAddress, unsigned short Port) = 0;

	virtual void SendHexPackets(uint8_t buffer) = 0;
	virtual void SendHexPackets(uint8_t buffer[]) = 0;
};

#endif