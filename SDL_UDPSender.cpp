#include <ctime>
#include <iomanip>
#include <iostream>
#include "SDL_UDPSender.h"
#include <chrono>
#include <SDL_net.h>
#include <string.h>


void SDL_UDPSender::InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal ) {
    char *host;
    
    if(SDL_Init(0)==-1) {
        printf("SDL_Init: %s\n", SDL_GetError());
    }
    
    if(SDLNet_Init() == -1) {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
    }
    
    udpsock=SDLNet_UDP_Open(Port);

    if(!udpsock) {
        printf("SDLNet_UDP_Open: %s\n", SDLNet_GetError());
    }
    
    if(SDLNet_ResolveHost(&address,IPAddress,Port) == -1)
	{
		printf("SDLNet_ResolveHost: %s\n",SDLNet_GetError());
		exit(4);
	}

    if(SDLNet_UDP_Bind(udpsock, 0, &address) == -1) {
        printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
    }
}

void SDL_UDPSender::SendHexPackets (uint8_t buffer) {
    uint8_t BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void SDL_UDPSender::SendHexPackets (uint8_t buffer[]) {
 
    int numsent;
    UDPpacket packet;
    packet.address = address;
    packet.data = buffer;
    packet.len = strlen((char*)buffer) -1;

    numsent=SDLNet_UDP_Send(udpsock, 0, &packet);
    if(!numsent) {
        printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
        // do something because we failed to send
        // this may just be because no addresses are bound to the channel...
    }
    SDL_Delay(DelayAfterPacketMS);
}
