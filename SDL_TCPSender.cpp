
#include <ctime>
#include <iomanip>
#include <iostream>
#include "SDL_TCPSender.h"
#include <chrono>
#include <SDL_net.h>

#include <string.h>
void SDL_TCPSender::InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal) {
    char *host;
    
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
    
    TCPsock = SDLNet_TCP_Open(&address);

    if(!TCPsock) {
        printf("SDLNet_TCP_Open: %s\n", SDLNet_GetError());
    }
    int len;
    char message[1024] = "Hello World";
    

    len = strlen(message);
    
    int result;
    result = SDLNet_TCP_Send(TCPsock , message , len);
    result = SDLNet_TCP_Send(TCPsock , message , len);
    SDLNet_TCP_Close(TCPsock);
    TCPsock = SDLNet_TCP_Open(&address);
    result = SDLNet_TCP_Send(TCPsock , message , len);
}

void SDL_TCPSender::SendHexPackets (uint8_t buffer) {
    uint8_t BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void SDL_TCPSender::SendHexPackets (uint8_t buffer[]) {
    int result;
    TCPsock = SDLNet_TCP_Open(&address);
    int len = strlen((char*)buffer);
    result = SDLNet_TCP_Send(TCPsock, buffer ,len -1);
    SDLNet_TCP_Close(TCPsock);
    if(result < len) {
		printf("SDLNet_TCP_Send: %s\n" , SDLNet_GetError());
    }
}
