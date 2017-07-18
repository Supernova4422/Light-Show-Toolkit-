#include "CommandDataTypes.cpp"
#include "Milight.h"

#define WIN32_LEAN_AND_MEAN
#include <winsock2.h>

#include <ctime>
#include <iomanip>



void Milight::EmitColour(const Colour OutputColour) {

}

bool UpdatedCurrentGroup = false;

void Milight::OnCurrentGroupsUpdate(GroupManager& Manager) {
    
    UDPPacketSender.InitialiseConnection("10.0.0.65",8899);
    
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
    int WhiteThreshhold = 10;
    int BrightnessThreshhold = 10;

    if (OutputColour.Saturation < WhiteThreshhold) {
        SetWhiteForCurrentGroups();
        std::cout << "SETTING WHITE" << std::endl;
    }
    else {
        bytes[0] = 0x40; 
        bytes[1] = 174 - OutputColour.Hue;
        bytes[2] = 0x55;
        SetColourForCurrentGroups(bytes);
        std::cout << "SETTING COLOUR" << std::endl;
    }
    
    std::cout << std::endl;
    
    if (OutputColour.Brightness < BrightnessThreshhold)
    {
        TurnCurrentGroupsOff();
        std::cout << "TURNING OFF" << std::endl;

    } else {
        char BrightnessBuffer[3];
        BrightnessBuffer[0] = 0x4E;
        BrightnessBuffer[1] = 2 + (( ( (float)OutputColour.Brightness) / 255) * 25);
        BrightnessBuffer[2] = 0x55; 
        SetColourForCurrentGroups(BrightnessBuffer);
    }
    
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
                std::cout << "SENDING ONE GROUP PACKET" << std::endl;
                UpdatedCurrentGroup = true;
                UDPPacketSender.SendHexPackets(CurrentGroupBytes[0]);
            }
            
            UDPPacketSender.SendHexPackets(ColourPacket);
    } else {
        for (char item : CurrentGroupBytes) {
            std::cout << item << std::endl;
            
            UDPPacketSender.SendHexPackets(item);
            
            //WAIT 100ms
            UDPPacketSender.SendHexPackets(ColourPacket);
        }
    }
}

void Milight::SetWhiteForCurrentGroups() {
    if (CurrentGroupBytes.size() == 1 ) {
            if (UpdatedCurrentGroup == false) {
                UpdatedCurrentGroup = true;
                UDPPacketSender.SendHexPackets(CurrentGroupBytes[0]);
            }
            UDPPacketSender.SendHexPackets(CurrentGroupBytes[0] + 128);
    } else {
        for (unsigned char item : CurrentGroupBytes) {
            UDPPacketSender.SendHexPackets(item);
            //WAIT 100ms
            UDPPacketSender.SendHexPackets(item + 128);
        }
    }
}

void Milight::TurnCurrentGroupsOff() {
    
    UpdatedCurrentGroup = false; //This ensures that LIGHTON functions are resent too 

    if (CurrentGroupBytes[0] == 0x42) {
            UDPPacketSender.SendHexPackets(0x42 - 1);
    } else {
        for (char item : CurrentGroupBytes) {
            UDPPacketSender.SendHexPackets(item + 1);
    }
    }
}

