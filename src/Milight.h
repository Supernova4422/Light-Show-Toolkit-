#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
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
    std::unique_ptr<NetworkPacketSender> PacketSender;
    CanUseByteForALLGROUPS CheckIfCanUseByteForALLGROUPS(const std::map<int, colour_combiner> Collection);
    Milight(int BrightnessThreshhold);

    void EmitColour(const Command CommandItem, const std::map<int, colour_combiner> ExpectedOutput);
    void OnCurrentGroupsUpdate(const Command CommandItem, std::map<int, colour_combiner> CurrentGroups);

    void SpecificCommand(const Command command);

private:
    int BrightnessThreshhold;
    MilightGroupIDs GetGroupEnum(int GroupNumber) const;
    uint8_t GetGroupHexByte(int GroupNumber) const;

    std::vector<uint8_t> CurrentGroupBytes;

    void SendHue(const Colour OutputColour);
    void SendBrightness(const Colour OutputColour);
    void SendGroupOn(MilightGroupIDs GroupID);
    void SendGroupOFF();
};