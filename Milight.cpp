#include "CommandDataTypes.cpp"
#include "Milight.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>




void Milight::EmitColour(const Colour OutputColour) {

}

bool UpdatedCurrentGroup = false;

void Milight::OnCurrentGroupsUpdate(GroupManager& Manager) {
    
    CurrentGroupBytes.clear();
    //These bools allow us to ensure no doubles occur, and question if all are in
    //We could probably replace this with a list that ensures unique values
    //And then check for "Four" inputs at the end
    UpdatedCurrentGroup = false;

    bool ContainsGroup1 = false;
    bool ContainsGroup2 = false;
    bool ContainsGroup3 = false;
    bool ContainsGroup4 = false;

    for (const int* item : Manager.CurrentlySelectedGroups) {
        if ((*item == 1) && (ContainsGroup1 == false))  {
            ContainsGroup1 = true;
            CurrentGroupBytes.push_back(GetGroupHexByte(*item));
        }
        if ((*item == 2) && (ContainsGroup2 == false))  {
            ContainsGroup2 = true;
            CurrentGroupBytes.push_back(GetGroupHexByte(*item));
        }
        if ((*item == 3) && (ContainsGroup3 == false))  {
            ContainsGroup3 = true;
            CurrentGroupBytes.push_back(GetGroupHexByte(*item));
        }
        if ((*item == 4) && (ContainsGroup4 == false))  {
            ContainsGroup4 = true;
            CurrentGroupBytes.push_back(GetGroupHexByte(*item));
        }
    }
    
    if ( ((ContainsGroup1 && ContainsGroup2) && (ContainsGroup3 && ContainsGroup4)) == true) {
        CurrentGroupBytes.clear();
        CurrentGroupBytes.push_back(0x42);
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
    bytes[1] = 174 - OutputColour.Hue;
    bytes[2] = 0x55;
    
    SetColourForCurrentGroups(bytes);
    std::cout << std::endl;
    
    char BrightnessBuffer[3];
    BrightnessBuffer[0] = 0x4E;
    BrightnessBuffer[1] = 2 + (( ( (float)OutputColour.Brightness) / 255) * 25);
    BrightnessBuffer[2] = 0x55; 
 
    SetColourForCurrentGroups(BrightnessBuffer);
    std::cout << std::endl;

    //Group Byte + 128 gives the inner value for brightness
} 

void Milight::RemoveColour(const Colour OutputColour) {
}

void Milight::SpecificCommand(const Command command){
}



   
void Milight::SetColourForCurrentGroups(const char ColourPacket[]) {
    //Right now the implementation is not working properly because packets are colliding
    //This can be fixed by adding a 100ms delay between setting groups, then the command for the group


    if (CurrentGroupBytes.size() == 1 ) {
            if (UpdatedCurrentGroup == false)
            {
                UpdatedCurrentGroup = true;
                SendHexPackets(CurrentGroupBytes[0]);
            }
            
            SendHexPackets(ColourPacket);
    } else {
        for (char item : CurrentGroupBytes) {
            SendHexPackets(item);
            
            //WAIT 100ms
            SendHexPackets(ColourPacket);
        }
    }
}

void Milight::SetWhiteForCurrentGroups() {
    if (CurrentGroupBytes.size() == 1 && UpdatedCurrentGroup == false) {
            UpdatedCurrentGroup = true;
            SendHexPackets(CurrentGroupBytes[0] + 128);
    } else {
        for (char item : CurrentGroupBytes) {
            //WAIT 100ms
            SendHexPackets(item + 128);
        }
    }
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
void Milight::SendHexPackets (const char buffer) {
    char BufferArray[1];
    BufferArray[0] = buffer;
    SendHexPackets(BufferArray);
}

void Milight::SendHexPackets (const char buffer[]) {
    int BufLen = sizeof(buffer);
    
    int iResult;
    for (int i = 0; i < BufLen -1; i++)
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