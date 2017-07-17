#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include "NetworkPacketSender.h"



void NetworkPacketSender::InitialiseConnection (const char * IPAddress , unsigned short Port, NetworkProtocal Protocal) {
    
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
    }    

    int ProtocalIdentifier;

    if (Protocal == UDP) {
        ProtocalIdentifier = IPPROTO_UDP;
    }
    if (Protocal == TCP) {
        ProtocalIdentifier = IPPROTO_TCP;
    }

    SendSocket = socket(AF_INET, SOCK_DGRAM, ProtocalIdentifier);
   
    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
    }
    
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr(IPAddress);
    
}

void NetworkPacketSender::SendHexPackets (const char buffer) {
    char BufferArray[0];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void NetworkPacketSender::SendHexPackets (const char buffer[]) {
    
    clock_t EndTime;
    EndTime = clock() + (100);
    while (clock() < EndTime) { 
    }

    int BufLen = sizeof(buffer);
    
    int iResult;
    for (int i = 0; i < BufLen - 1; i++)
    {
        std::cout << (int)buffer[i] << " , " ;
    }
    std::cout << std::endl;
    iResult = sendto(SendSocket, buffer, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
    }
}
