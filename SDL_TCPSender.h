#include "NetworkPacketSender.h"
#include <SDL2/SDL_net.h>
class SDL_TCPSender : public NetworkPacketSender {


public: 
void InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal = UDP);

void SendHexPackets (uint8_t buffer);
void SendHexPackets (uint8_t buffer[]);
private: 
TCPsocket TCPsock;
IPaddress address;
};
