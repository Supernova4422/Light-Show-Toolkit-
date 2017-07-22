#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include "NetworkPacketSender.h"
#include <chrono>
#include <SDL_net.h>

UDPsocket udpsock;
IPaddress *address;

void NetworkPacketSender::InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal) {
    	
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
    int channel;

    //channel=SDLNet_UDP_Bind(udpsock, -1, address);
    //if(channel==-1) {
   //     printf("SDLNet_UDP_Bind: %s\n", SDLNet_GetError());
        // do something because we failed to bind
    //}
}

void NetworkPacketSender::SendHexPackets (uint8_t buffer) {
    uint8_t BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void NetworkPacketSender::SendHexPackets (uint8_t buffer[]) {
 
    int numsent;
    UDPpacket packet;
    packet.address = *address;
    packet.data = buffer;
    packet.len = sizeof(buffer);

    numsent=SDLNet_UDP_Send(udpsock, 0, &packet);
    if(!numsent) {
        printf("SDLNet_UDP_Send: %s\n", SDLNet_GetError());
        // do something because we failed to send
        // this may just be because no addresses are bound to the channel...
    }

}
