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
} 

void Milight::RemoveColour(const Colour OutputColour) {
}

void Milight::SpecificCommand(const Command command){
}


SOCKET SendSocket = INVALID_SOCKET;
sockaddr_in RecvAddr;
   

void Milight::InitialiseUDPConnection (const char * IPAddress , unsigned short Port) {
    
    WSADATA wsaData;
    int iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (iResult != NO_ERROR) {
        wprintf(L"WSAStartup failed with error: %d\n", iResult);
    }    

    SendSocket = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
   
    if (SendSocket == INVALID_SOCKET) {
        wprintf(L"socket failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
    }
    
    
    RecvAddr.sin_family = AF_INET;
    RecvAddr.sin_port = htons(Port);
    RecvAddr.sin_addr.s_addr = inet_addr(IPAddress);
    
}

void Milight::SendHexPackets (char buffer[]) {
    int BufLen = sizeof(buffer);
    
    int iResult;
    iResult = sendto(SendSocket, buffer, BufLen, 0, (SOCKADDR *) & RecvAddr, sizeof (RecvAddr));

    if (iResult == SOCKET_ERROR) {
        wprintf(L"sendto failed with error: %d\n", WSAGetLastError());
        closesocket(SendSocket);
        WSACleanup();
    }

}