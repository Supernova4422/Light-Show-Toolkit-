#include "CommandDataTypes.cpp"
#include "Milight.h"

#include <ctime>
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <errno.h>
#include "SDL_UDPSender.h"
#include "SDL_TCPSender.h"


SDL_TCPSender TCPSender;
SDL_UDPSender UDPSender;

Milight::Milight() {
    std::cout << "MiLight" << std::endl;
    const std::string SettingsFile = "MiLightSettings.txt";
    std::ifstream myfile(SettingsFile);
    
    const char * IPAddress = "255.255.255.255";
    unsigned short Port = 8899;
    NetworkProtocal Protocal = NetworkProtocal::UDP;
    int DelayAfterPacketMS; 
    if (myfile.is_open()) {
        
        
        std::string IPAsString; 
        getline(myfile,IPAsString);
        IPAddress = IPAsString.c_str();
        std::string CurrentLine;
        getline(myfile,CurrentLine);
        Port = (unsigned short) std::stoi(CurrentLine, NULL, 0);

        getline(myfile,CurrentLine);
        if ( CurrentLine == "TCP") {
            Protocal = NetworkProtocal::TCP;
        }
        else {
            Protocal = NetworkProtocal::UDP;
        }
        getline(myfile,CurrentLine);
        DelayAfterPacketMS = std::stoi(CurrentLine, NULL, 0);

    }
    std::cout << "Loaded with the following settings:" << std::endl;
    std::cout << "  IP Address: " << IPAddress << std::endl;   
    std::cout << "  Port: " << Port << std::endl;
    std::cout << "  Protocal: ";
    
    switch (Protocal)
    {
        case TCP: 
            TCPSender = SDL_TCPSender();
            PacketSender = &TCPSender;
            std::cout << "TCP" << std::endl;
            TCPSender.InitialiseConnection(IPAddress, Port, Protocal);
        break;

        case UDP: 
            UDPSender = SDL_UDPSender();
            UDPSender.DelayAfterPacketMS = DelayAfterPacketMS;
            PacketSender = &UDPSender;
            std::cout << "UDP" << std::endl;
            std::cout << "  Delay after each packet:" << DelayAfterPacketMS << "MS" << std::endl;
            UDPSender.InitialiseConnection(IPAddress, Port, Protocal);
        break;
    }
    std::cout << "  Networking Initialised" << std::endl;
    
    std::cout <<  std::endl <<  std::endl;
}

void Milight::EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput) {
    
    CanUseByteForALLGROUPS CanSendAllGroupByte = CheckIfCanUseByteForALLGROUPS(ExpectedOutput);
    if (ExpectedOutput.size() > 0) {

        //COLOUR MUST ALWAYS BE SENT FIRST
        Colour FirstEntryColour = ExpectedOutput[0]->second;

        switch (CanSendAllGroupByte)
        {
            case ForBoth:
            //Send Group Byte
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            
            //Send Hue
            SendHue(FirstEntryColour);
            
            //Individually send brightness 
            SendBrightness( FirstEntryColour);
            
            break;
            
            case ForHue:
            //Send Group Byte
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            
            //Send Hue
            SendHue(FirstEntryColour);
            
            //Individually send brightness 
            for (std::pair<const int, Colour>* entry : ExpectedOutput ) {
                if ((entry->first < 5) && (entry->first > 0)) {
                    
                    SendGroupOn(GetGroupEnum(entry->first));
                    
                    SendBrightness( entry->second);
                }
            }

            break;
            
            case ForBrightness:

            //Individually send Hue 
            for (std::pair<const int, Colour>* entry : ExpectedOutput ) {
                if ((entry->first < 5) && (entry->first > 0)) {
                    
                    SendGroupOn(GetGroupEnum(entry->first));

                    SendHue( entry->second);
                }
            }
            //Send GroupByte
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            
            //Send Brightness
            SendBrightness(FirstEntryColour);

            break;
            case ForNeither:
            //Individually send Hue, then Brightness
            for (std::pair<const int, Colour>* entry : ExpectedOutput ) {
                if ((entry->first < 5) && (entry->first > 0)) {
                    
                    SendGroupOn(GetGroupEnum(entry->first));

                    SendHue( entry->second);
                    SendBrightness( entry->second);
                }
            }

            break;
        }
    }
}


bool UpdatedCurrentGroup = false;

CanUseByteForALLGROUPS Milight::CheckIfCanUseByteForALLGROUPS (const std::vector<std::pair<const int, Colour>*> Collection) {
    
    bool AllHuesAreSame = false;
    bool AllBrightnessAreSame = false;

    
    int NumberOfUniqueGroups = 0;
    CanUseByteForALLGROUPS ret = ForBoth;
    uint8_t Hue = 0;
    uint8_t Brightness = 0;
    
    bool ContainsGroup1 = false;
    bool ContainsGroup2 = false;
    bool ContainsGroup3 = false;
    bool ContainsGroup4 = false;
    
    for (std::pair<const int, Colour>* item : Collection) {
        if ((item->first == 1) && (ContainsGroup1 == false))  {
            ContainsGroup1 = true;
            NumberOfUniqueGroups++;
        }
        if ((item->first == 2) && (ContainsGroup2 == false))  {
            ContainsGroup2 = true;
            NumberOfUniqueGroups++;
        }
        if ((item->first == 3) && (ContainsGroup3 == false))  {
            ContainsGroup3 = true;
            NumberOfUniqueGroups++;
        }
        if ((item->first == 4) && (ContainsGroup4 == false))  {
            ContainsGroup4 = true;
            NumberOfUniqueGroups++;
        }
        if (NumberOfUniqueGroups == 1 ) {
            Hue = item->second.Hue;
            Brightness = item->second.Brightness;
        }
        if (NumberOfUniqueGroups > 1) {
            if (item->second.Hue != Hue) {
                ret = (CanUseByteForALLGROUPS) (ret & ~ForHue);  //Performs bitwise subtraction
            }
            if (item->second.Brightness != Brightness) {
                ret = (CanUseByteForALLGROUPS) (ret & ~ForBrightness); //Performs bitwise subtraction
                AllBrightnessAreSame = false;
            }
        }
    }
    if ( NumberOfUniqueGroups != 4) {
        ret = ForNeither;
    }

    return ret;
}
void Milight::OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups) {
    
    
    //These bools allow us to ensure no doubles occur, and question if all are in
    //We could probably replace this with a list that ensures unique values
    //And then check for "Four" inputs at the end
    
    bool ContainsGroup1 = false;
    bool ContainsGroup2 = false;
    bool ContainsGroup3 = false;
    bool ContainsGroup4 = false;
        

    for (std::pair<const int, Colour>* item : CurrentGroups) {
        if ((item->first == 1) && (ContainsGroup1 == false))  {
            ContainsGroup1 = true;
        }
        if ((item->first == 2) && (ContainsGroup2 == false))  {
            ContainsGroup2 = true;
        }
        if ((item->first == 3) && (ContainsGroup3 == false))  {
            ContainsGroup3 = true;
        }
        if ((item->first == 4) && (ContainsGroup4 == false))  {
            ContainsGroup4 = true;
        }
    }
    
    //We send the packet in advance, this means that the delay time can be concealed in following "WAIT" commands
    if ( ((ContainsGroup1 && ContainsGroup2) && (ContainsGroup3 && ContainsGroup4)) == true) {
        PacketSender->SendHexPackets( 0x42 );
    } else if (CurrentGroups.size() == 1) {
        
        const int GroupID = CurrentGroups[0]->first;
        
        if ((GroupID > 0) && (GroupID < 5)) {
            SendGroupOn(GetGroupEnum(GroupID));
        }
    }
}
MilightGroupIDs Milight::GetGroupEnum(int GroupNumber) {
    MilightGroupIDs GroupIDEnum;
    if (GroupNumber == 1) {
        GroupIDEnum = Group1;
    }
    if (GroupNumber == 2) {
        GroupIDEnum = Group2;
    }
    if (GroupNumber == 3) {
        GroupIDEnum = Group3;
    }
    if (GroupNumber == 4) {
        GroupIDEnum = Group4;
    }

    return GroupIDEnum;
}

uint8_t  Milight::GetGroupHexByte(int GroupNumber) {
    //Group 1 ALL ON is 0x45, Group 2 ALL ON is 0x47, and so on

    uint8_t GroupHex = 0x43; //If group is 1, this will increment to 1 on execute
    for (int i = 0; i < GroupNumber ; i++) {
            GroupHex++;
            GroupHex++;
    }
    
    return GroupHex;
}

uint8_t LastGroupPacketSent = 0x00; 

void Milight::SendGroupOn(MilightGroupIDs GroupID)
{
    
    uint8_t ByteToSend;

    if (GroupID == ALLGROUPS ) {
        ByteToSend = 0x42;
    } else if (GroupID != Invalid) {
        ByteToSend = GetGroupHexByte(GroupID);
    }
    
    if ((GroupID != Invalid) && (LastGroupPacketSent != ByteToSend)) {
        LastGroupPacketSent = ByteToSend;
        PacketSender->SendHexPackets(ByteToSend);
        std::cout << "Sent Group ON" << std::endl;
    }
}

void Milight::SendGroupOFF()
{
    if (LastGroupPacketSent == 0x42) {
            PacketSender->SendHexPackets(0x41);
            LastGroupPacketSent = LastGroupPacketSent - 1;
        }
        else {
            LastGroupPacketSent = LastGroupPacketSent + 1;
            PacketSender->SendHexPackets(LastGroupPacketSent + 1);
    }
}


void Milight::SendHue(const Colour OutputColour)
{
    uint8_t bytes[3];
    int WhiteThreshhold = 10;
    
    if (OutputColour.Saturation < WhiteThreshhold) {
        std::cout << "Milight is sending the Color: WHITE" << std::endl;
        PacketSender->SendHexPackets(LastGroupPacketSent + 128);
        
    }
    else {
        bytes[0] = 0x40; 
        bytes[1] = 174 - OutputColour.Hue;
        bytes[2] = 0x55;
        std::cout << "Milight is sending the Color: " << (int) bytes[1] << std::endl;
        PacketSender->SendHexPackets(bytes);
        
    }
}

void Milight::SendBrightness(const Colour OutputColour)
{
    int BrightnessThreshhold = 10;
    if (OutputColour.Brightness < BrightnessThreshhold)
    {
        std::cout << "Milight is turning off the lights" << std::endl;
        std::cout << "TURNING OFF: " << std::endl;
        SendGroupOFF();
        
        
    }  else {
        std::cout << "SETTING BRIGHTNESS: " << std::endl;
        uint8_t BrightnessBuffer[3];
        BrightnessBuffer[0] = 0x4E;
        BrightnessBuffer[1] = 2 + (( ( (float)OutputColour.Brightness) / 255) * 24);
        BrightnessBuffer[2] = 0x55; 
        std::cout << "Milight is sending the brightness code: " << (int) BrightnessBuffer[1] << std::endl;
        PacketSender->SendHexPackets(BrightnessBuffer);
    }
}

void Milight::SpecificCommand(const Command command){
    if (command.value == "OFF") {
        SendGroupOFF();
    }
}



 



