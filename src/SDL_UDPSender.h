#include "NetworkPacketSender.h"
#include "SDL_net.h"
class SDL_UDPSender : public NetworkPacketSender {
	public:

	void InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal = UDP);
	void SendHexPackets (uint8_t buffer);
	void SendHexPackets (uint8_t buffer[]);

	~SDL_UDPSender()
	{
		SDLNet_UDP_Close(udpsock);
		udpsock = NULL;
	}


private:
	UDPsocket udpsock;
	IPaddress address;
};