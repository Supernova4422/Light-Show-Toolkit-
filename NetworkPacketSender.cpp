#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include <ctime>
#include <iomanip>
#include <iostream>
#include "NetworkPacketSender.h"
#include <chrono>


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

void NetworkPacketSender::SendHexPackets (const uint8_t buffer) {
    uint8_t BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void NetworkPacketSender::SendHexPackets (const uint8_t buffer[]) {

    
    int BufLen = sizeof(buffer);
    
    int iResult;

    for (int i = 0; i < BufLen; i++)
    {
        std::cout << (int)buffer[i] << " , " ;
    }
    std::cout << std::endl;
    for (int i = 0 ; i < 5 ; i++) {
        iResult = sendto(SendSocket, (const char*) &buffer[0], BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));
    }
    
    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
    }

    std::chrono::high_resolution_clock::time_point SongStartTime = std::chrono::high_resolution_clock::now();
    
    while (std::chrono::high_resolution_clock::now() < (SongStartTime + std::chrono::milliseconds(500) ) ) { 
        //Do nothing
    }

}
