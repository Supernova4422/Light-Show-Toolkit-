#pragma once
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include <vector>
#include "NetworkPacketSender.h"

enum CanUseByteForALLGROUPS
{
    ForNeither = 0x00,    //"00000000"
    ForHue = 0x01,        //"00000001"
    ForBrightness = 0x02, //"00000010"
    ForBoth = 0x03        //"00000011"
};

enum MilightGroupIDs
{
    Invalid = 0,
    Group1 = 1,
    Group2 = 2,
    Group3 = 3,
    Group4 = 4,
    ALLGROUPS = 5
};

class Milight : public ProgrammableLight
{
public:
    CanUseByteForALLGROUPS CheckIfCanUseByteForALLGROUPS(const std::map<int, Colour_Combiner> Collection);
    Milight(int BrightnessThreshhold);

    void EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput) override;

    void OnCurrentGroupsUpdate(const Command CommandItem, std::map<int, Colour_Combiner> CurrentGroups) override;

    void SpecificCommand(const Command command, const std::map<int, Colour_Combiner> CurrentGroups) override;

    void OnStart() override{}; //TODO

    void OnEnd() override{}; //TODO

private:
    int BrightnessThreshhold;
    MilightGroupIDs GetGroupEnum(const int GroupNumber) const;
    uint8_t GetGroupHexByte(const int GroupNumber) const;
    std::unique_ptr<NetworkPacketSender> PacketSender;
    std::vector<uint8_t> CurrentGroupBytes;
    uint8_t LastGroupPacketSent = 0x00;

    void SendHue(const Colour OutputColour);
    void SendBrightness(const Colour OutputColour);
    void SendGroupOn(const MilightGroupIDs GroupID);
    void SendGroupOFF();
};