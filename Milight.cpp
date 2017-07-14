#include "CommandDataTypes.cpp"
#include "Milight.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

void Milight::SetColourForCurrentGroups(const Colour OutputColour) {
    
}

void Milight::EmitColour(const Colour OutputColour) {

}

void Milight::OnCurrentGroupsUpdate(GroupManager& Manager) {

}

void Milight::AddColour(const Colour OutputColour) {
}

void Milight::SetColour(const Colour OutputColour) {
    
    unsigned short Port = 8899;
    SOCKET SendSocket = INVALID_SOCKET;
    
    char buffer[3]={0x4E,0x11,0x55}; //This will change brightness
    
    int BufLen = sizeof(buffer);
     
    int iResult;
    
    WSADATA wsaData;

    iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
    }

    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    

    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
    }
    sockaddr_in RecvAddr;
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr("10.0.0.65");

    iResult = sendto(SendSocket, buffer, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));

    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
    }

    
    char byte = 0x11;
    send(SendSocket,&byte,1,0);
    
} 

void Milight::RemoveColour(const Colour OutputColour) {
}

void Milight::SpecificCommand(const Command command){
}

