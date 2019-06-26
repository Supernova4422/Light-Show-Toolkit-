#include <ctime>
#include <iomanip>
#include <iostream>
#include "SDL_UDPSender.h"
#include <chrono>
#include "SDL_net.h"
#include <string.h>

void SDL_UDPSender::InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal ) {

    if(SDL_Init(0)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }

    if(SDLNet_Init() == -1) {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
    }

    if(SDLNet_ResolveHost(&address,IPAddress,Port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(4);
	}
}

void SDL_UDPSender::SendHexPackets (uint8_t buffer) {
    uint8_t BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void SDL_UDPSender::SendHexPackets (uint8_t buffer[]) {

    udpsock = SDLNet_UDP_Open(8900);

    if(!udpsock) {
        printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    }

    UDPpacket packet;
    packet.address = address;
    packet.data = buffer;
    packet.len = strlen((char*)buffer) -1 ;


    if (SDLNet_UDP_Send(udpsock, -1, &packet) == 0) {
        std::cout << "\tSDLNet_UDP_Send failed : " << SDLNet_GetError() << "\n";
    }

    SDLNet_UDP_Close(udpsock);

    SDL_Delay(DelayAfterPacketMS);
}
