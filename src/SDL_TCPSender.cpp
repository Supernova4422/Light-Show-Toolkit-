
#include <ctime>
#include <iomanip>
#include <iostream>
#include "SDL_TCPSender.h"
#include <chrono>
#include "SDL.h"
#include "SDL_net.h"
#include <string.h>
#include <stdio.h>
void SDL_TCPSender::InitialiseConnection(const char *IPAddress, unsigned short Port)
{
    if (SDL_Init(0) == -1)
    {
        printf("SDL_Init: %s\n", SDL_GetError());
    }

    if (SDLNet_Init() == -1)
    {
        printf("SDLNet_Init: %s\n", SDLNet_GetError());
    }

    if (SDLNet_ResolveHost(&address, IPAddress, Port) == -1)
    {
        printf("SDLNet_ResolveHost: %s\n", SDLNet_GetError());
    }
}

void SDL_TCPSender::SendHexPackets(uint8_t buffer)
{
    uint8_t BufferArray[3];
    BufferArray[0] = buffer;
    BufferArray[1] = 0x00;
    BufferArray[2] = 0x55;
    SendHexPackets(BufferArray);
}

void SDL_TCPSender::SendHexPackets(uint8_t buffer[])
{

    TCPsock = SDLNet_TCP_Open(&address);

    int len = strlen((char *)buffer);
    int result;
    if (len == 1)
    {
        buffer[1] = 0x00;
        result = SDLNet_TCP_Send(TCPsock, buffer, len + 1);
    }
    else
    {
        result = SDLNet_TCP_Send(TCPsock, buffer, len);
    }

    SDLNet_TCP_Close(TCPsock);
}
