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

Milight::Milight(const int BrightnessThreshhold)
{
    this->BrightnessThreshhold = BrightnessThreshhold;
    std::cout << "MiLight" << std::endl;
    std::ifstream myfile("MiLightSettings.txt");

    std::string IPAddress = "255.255.255.255";
    unsigned short Port = 8899;
    NetworkProtocal Protocal = NetworkProtocal::UDP;
    int DelayAfterPacketMS = 0;
    if (myfile.is_open())
    {
        std::cout << "Opened config for milight" << std::endl;
        std::string IPAsString;
        getline(myfile, IPAddress);
        std::cout << IPAddress << std::endl;
        std::string CurrentLine;
        getline(myfile, CurrentLine);
        Port = (unsigned short)std::stoi(CurrentLine, NULL, 0);

        getline(myfile, CurrentLine);
        if (CurrentLine[0] == 'T')
        {
            Protocal = NetworkProtocal::TCP;
        }
        else
        {
            Protocal = NetworkProtocal::UDP;
        }
        getline(myfile, CurrentLine);
        DelayAfterPacketMS = std::stoi(CurrentLine, NULL, 0);
    }
    else
    {
        std::cout << "Using Default config" << std::endl;
    }
    std::cout << "Loaded with the following settings:" << std::endl;
    std::cout << "  IP Address: " << IPAddress << std::endl;
    std::cout << "  Port: " << Port << std::endl;
    std::cout << "  Protocal: ";

    switch (Protocal)
    {
    case TCP:
        PacketSender = std::make_unique<SDL_TCPSender>();
        std::cout << "TCP" << std::endl;
        break;

    case UDP:
        std::cout << "  Delay after each packet:" << DelayAfterPacketMS << "MS" << std::endl;
        PacketSender = std::make_unique<SDL_UDPSender>(DelayAfterPacketMS);
        std::cout << "UDP" << std::endl;
        break;
    }
    PacketSender->InitialiseConnection(IPAddress.c_str(), Port);

    std::cout << "  Networking Initialised" << std::endl;
    std::cout << std::endl
              << std::endl;
}

void Milight::EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput)
{
    CanUseByteForALLGROUPS CanSendAllGroupByte = CheckIfCanUseByteForALLGROUPS(ExpectedOutput);
    if (ExpectedOutput.size() > 0)
    {
        //COLOUR MUST ALWAYS BE SENT FIRST
        Colour FirstEntryColour = ExpectedOutput.begin()->second.get_colour();

        switch (CanSendAllGroupByte)
        {
        case ForBoth:
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            SendHue(FirstEntryColour);
            SendBrightness(FirstEntryColour);
            break;

        case ForHue:
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            SendHue(FirstEntryColour);
            for (auto entry : ExpectedOutput)
            {
                if ((entry.first < 5) && (entry.first > 0))
                {
                    SendGroupOn(GetGroupEnum(entry.first));
                    SendBrightness(entry.second.get_colour());
                }
            }
            break;

        case ForBrightness:
            for (auto entry : ExpectedOutput)
            {
                if ((entry.first < 5) && (entry.first > 0))
                {
                    SendGroupOn(GetGroupEnum(entry.first));
                    SendHue(entry.second.get_colour());
                }
            }
            SendGroupOn(MilightGroupIDs::ALLGROUPS);
            SendBrightness(FirstEntryColour);
            break;

        case ForNeither:
            for (auto entry : ExpectedOutput)
            {
                if ((entry.first < 5) && (entry.first > 0))
                {
                    SendGroupOn(GetGroupEnum(entry.first));
                    SendHue(entry.second.get_colour());
                    SendBrightness(entry.second.get_colour());
                }
            }
            break;
        }
    }
}

bool UpdatedCurrentGroup = false;

CanUseByteForALLGROUPS Milight::CheckIfCanUseByteForALLGROUPS(const std::map<int, Colour_Combiner> Collection)
{
    bool AllBrightnessAreSame = false;
    int NumberOfUniqueGroups = 0;
    CanUseByteForALLGROUPS ret = ForBoth;
    uint8_t Hue = 0;
    uint8_t Brightness = 0;

    bool ContainsGroup1 = false;
    bool ContainsGroup2 = false;
    bool ContainsGroup3 = false;
    bool ContainsGroup4 = false;

    for (auto item : Collection)
    {
        if ((item.first == 1) && (ContainsGroup1 == false))
        {
            ContainsGroup1 = true;
            NumberOfUniqueGroups++;
        }
        if ((item.first == 2) && (ContainsGroup2 == false))
        {
            ContainsGroup2 = true;
            NumberOfUniqueGroups++;
        }
        if ((item.first == 3) && (ContainsGroup3 == false))
        {
            ContainsGroup3 = true;
            NumberOfUniqueGroups++;
        }
        if ((item.first == 4) && (ContainsGroup4 == false))
        {
            ContainsGroup4 = true;
            NumberOfUniqueGroups++;
        }
        if (NumberOfUniqueGroups == 1)
        {
            Hue = item.second.get_colour().Hue;
            Brightness = item.second.get_colour().Brightness;
        }
        if (NumberOfUniqueGroups > 1)
        {
            if (item.second.get_colour().Hue != Hue)
            {
                ret = (CanUseByteForALLGROUPS)(ret & ~ForHue); //Performs bitwise subtraction
            }
            if (item.second.get_colour().Brightness != Brightness)
            {
                ret = (CanUseByteForALLGROUPS)(ret & ~ForBrightness); //Performs bitwise subtraction
                AllBrightnessAreSame = false;
            }
        }
    }
    if (NumberOfUniqueGroups != 4)
    {
        ret = ForNeither;
    }

    return ret;
}
void Milight::OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, Colour_Combiner> CurrentGroups)
{
    //These bools allow us to ensure no doubles occur, and question if all are in
    //We could probably replace this with a list that ensures unique values
    //And then check for "Four" inputs at the end

    bool ContainsGroup1 = false;
    bool ContainsGroup2 = false;
    bool ContainsGroup3 = false;
    bool ContainsGroup4 = false;

    for (auto item : CurrentGroups)
    {
        if ((item.first == 1) && (ContainsGroup1 == false))
        {
            ContainsGroup1 = true;
        }
        if ((item.first == 2) && (ContainsGroup2 == false))
        {
            ContainsGroup2 = true;
        }
        if ((item.first == 3) && (ContainsGroup3 == false))
        {
            ContainsGroup3 = true;
        }
        if ((item.first == 4) && (ContainsGroup4 == false))
        {
            ContainsGroup4 = true;
        }
    }

    //We send the packet in advance, this means that the delay time can be concealed in following "WAIT" commands
    if (((ContainsGroup1 && ContainsGroup2) && (ContainsGroup3 && ContainsGroup4)) == true)
    {
        PacketSender->SendHexPackets(0x42);
    }
    else if (CurrentGroups.size() == 1)
    {

        const int GroupID = CurrentGroups.begin()->first;

        if ((GroupID > 0) && (GroupID < 5))
        {
            SendGroupOn(GetGroupEnum(GroupID));
        }
    }
}
MilightGroupIDs Milight::GetGroupEnum(int GroupNumber) const
{
    MilightGroupIDs GroupIDEnum;
    if (GroupNumber == 1)
    {
        GroupIDEnum = Group1;
    }
    if (GroupNumber == 2)
    {
        GroupIDEnum = Group2;
    }
    if (GroupNumber == 3)
    {
        GroupIDEnum = Group3;
    }
    if (GroupNumber == 4)
    {
        GroupIDEnum = Group4;
    }

    return GroupIDEnum;
}

uint8_t Milight::GetGroupHexByte(const int GroupNumber) const
{
    //Group 1 ALL ON is 0x45, Group 2 ALL ON is 0x47, and so on

    uint8_t GroupHex = 0x43; //If group is 1, this will increment to 1 on execute
    for (int i = 0; i < GroupNumber; i++)
    {
        GroupHex++;
        GroupHex++;
    }

    return GroupHex;
}

void Milight::SendGroupOn(const MilightGroupIDs GroupID)
{
    uint8_t bytes[3];
    bytes[1] = 0x00;
    bytes[2] = 0x55;
    if (GroupID == ALLGROUPS)
    {
        bytes[0] = 0x42;
    }
    else if (GroupID != Invalid)
    {
        bytes[0] = GetGroupHexByte(GroupID);
    }

    if ((GroupID != Invalid) && (LastGroupPacketSent != bytes[0]))
    {
        LastGroupPacketSent = bytes[0];

        PacketSender->SendHexPackets(bytes);
        std::cout << "Sent Group ON" << std::endl;
    }
}

void Milight::SendGroupOFF()
{
    if (LastGroupPacketSent == 0x42)
    {
        PacketSender->SendHexPackets(0x41);
        LastGroupPacketSent = LastGroupPacketSent - 1;
    }
    else
    {
        LastGroupPacketSent = LastGroupPacketSent + 1;
        PacketSender->SendHexPackets(LastGroupPacketSent + 1);
    }
}

void Milight::SendHue(const Colour OutputColour)
{
    uint8_t bytes[3];
    int WhiteThreshhold = 10;

    if (OutputColour.Saturation < WhiteThreshhold)
    {
        std::cout << "Milight is sending the Colour: WHITE" << std::endl;
        PacketSender->SendHexPackets(LastGroupPacketSent + 128);
    }
    else
    {
        bytes[0] = 0x40;
        bytes[1] = 174 - OutputColour.Hue;
        bytes[2] = 0x55;
        std::cout << "Milight is sending the Colour: " << (int)bytes[1] << std::endl;
        PacketSender->SendHexPackets(bytes);
    }
}

void Milight::SendBrightness(const Colour OutputColour)
{

    if (OutputColour.Brightness < BrightnessThreshhold)
    {
        std::cout << "Milight is turning off the lights" << std::endl;
        std::cout << "TURNING OFF: " << std::endl;
        SendGroupOFF();
    }
    else
    {
        std::cout << "SETTING BRIGHTNESS: " << std::endl;
        uint8_t BrightnessBuffer[3];
        BrightnessBuffer[0] = 0x4E;
        BrightnessBuffer[1] = 2 + ((((float)OutputColour.Brightness) / 255) * 24);
        BrightnessBuffer[2] = 0x55;
        std::cout << "Milight is sending the brightness code: " << (int)BrightnessBuffer[1] << std::endl;
        PacketSender->SendHexPackets(BrightnessBuffer);
    }
}

void Milight::SpecificCommand(const Command command, const std::map<int, Colour_Combiner> CurrentGroups)
{
    if (command.value == "OFF")
    {
        SendGroupOFF();
    }
}
