#pragma once
#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include <vector>
#include "NetworkPacketSender.h"

//ML Means milight
namespace ML_BYTES
{
enum CAN_USE_FOR_ALL_ALL_GROUPS
{
    ForNeither = 0x00,    //"00000000"
    ForHue = 0x01,        //"00000001"
    ForBrightness = 0x02, //"00000010"
    ForBoth = 0x03        //"00000011"
};

enum GROUP_ID
{
    Invalid = 0,
    Group1 = 1,
    Group2 = 2,
    Group3 = 3,
    Group4 = 4,
    ALLGROUPS = 5
};
} // namespace ML_BYTES

class Milight : public ProgrammableLight
{
public:
    ML_BYTES::CAN_USE_FOR_ALL_ALL_GROUPS GetNumOfPossibleGroups(const std::map<int, Colour_Combiner> Collection) const;
    Milight(int BrightnessThreshhold);

    void EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput) override;

    void OnCurrentGroupsUpdate(const Command CommandItem, std::map<int, Colour_Combiner> CurrentGroups) override;

    void SpecificCommand(const Command command, const std::map<int, Colour_Combiner> CurrentGroups) override;

    void OnStart() override{}; //TODO

    void OnEnd() override{}; //TODO

private:
    int BrightnessThreshhold;
    ML_BYTES::GROUP_ID GetGroupEnum(const int GroupNumber) const;
    uint8_t GetGroupHexByte(const int GroupNumber) const;
    std::unique_ptr<NetworkPacketSender> PacketSender;
    std::vector<uint8_t> CurrentGroupBytes;
    uint8_t LastGroupPacketSent = 0x00;

    void SendHue(const Colour OutputColour);
    void SendBrightness(const Colour OutputColour);
    void SendGroupOn(const ML_BYTES::GROUP_ID GroupID);
    void SendGroupOFF();
};