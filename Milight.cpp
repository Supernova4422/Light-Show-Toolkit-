#include "CommandDataTypes.cpp"
#include "Milight.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

void Milight::SetColourForCurrentGroups(const Colour OutputColour) {
    
}

void Milight::EmitColour(const Colour OutputColour) {

}


void Milight::OnCurrentGroupsUpdate(GroupManager& Manager) {
    

    if (Manager.CurrentlySelectedGroups.size() == 1) {
        int GroupNumber = *Manager.CurrentlySelectedGroups[0];
        char byte[1];
        byte[0] = GetGroupHexByte(GroupNumber);
        SendHexPackets(byte);
    } else {
        bool ContainsGroup1 = false;
        bool ContainsGroup2 = false;
        bool ContainsGroup3 = false;
        bool ContainsGroup4 = false;

        for (const int* item : Manager.CurrentlySelectedGroups) {
            if (*item == 1) {
                ContainsGroup1 = true;
            }
            if (*item == 2) {
                ContainsGroup2 = true;
            }
            if (*item == 3) {
                ContainsGroup3 = true;
            }
            if (*item == 4) {
                ContainsGroup4 = true;
            }
        }
        if (ContainsGroup1 == ContainsGroup2 == ContainsGroup3 == ContainsGroup4 == true) {
            char byte[0];
            byte[0] = 0x42; //ALLGROUPS
            SendHexPackets(byte);
        }
    }
}

char  Milight::GetGroupHexByte(int GroupNumber) {
    //Group 1 ALL ON is 0x45, Group 2 ALL ON is 0x47, and so on

    char GroupHex = 0x43; //If group is 1, this will increment to 1 on execute

    for (int i = 0; i < GroupNumber ; i++) {
            GroupHex++;
            GroupHex++;
    }
    return GroupHex;
}

void Milight::AddColour(const Colour OutputColour) {
}

void Milight::SetColour(const Colour OutputColour) {
    char bytes[3];
    bytes[0] = 0x40; 
    bytes[1] = OutputColour.Hue;
    bytes[2] = 0x55;
   
    SendHexPackets(bytes);SendHexPackets(bytes);SendHexPackets(bytes);
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