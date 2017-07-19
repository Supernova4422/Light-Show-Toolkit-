
#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include <ctime>
#include <iomanip>
enum NetworkProtocal { TCP, UDP};

class NetworkPacketSender {

SOCKET SendSocket = INVALID_SOCKET;
sockaddr_in RecvAddr;
public: 
void InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal = UDP);

void SendHexPackets (const uint8_t buffer);
void SendHexPackets (const uint8_t buffer[]);
};


