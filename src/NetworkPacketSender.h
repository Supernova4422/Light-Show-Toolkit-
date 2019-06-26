
#ifndef NETWORKPACKETSENDER_H
#define NETWORKPACKETSENDER_H
#include <ctime>
#include <iomanip>
enum NetworkProtocal { TCP, UDP};

class NetworkPacketSender {

public:
	virtual ~NetworkPacketSender() = default;
	virtual void InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal = UDP) = 0;

	virtual void SendHexPackets (uint8_t buffer) = 0;
	virtual void SendHexPackets (uint8_t buffer[]) = 0;
	unsigned int DelayAfterPacketMS = 0;
};



#endif