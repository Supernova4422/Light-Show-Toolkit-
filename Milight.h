#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
#include <vector>
#include "NetworkPacketSender.h"

enum CanUseByteForALLGROUPS {
    ForNeither = 0x00, //"00000000"
    ForHue = 0x01, //"00000001"
    ForBrightness = 0x02, //"00000010"
    ForBoth = 0x03 //"00000011"
};

enum MilightGroupIDs {Invalid = 0,  Group1 = 1, Group2 = 2, Group3 = 3, Group4 = 4, ALLGROUPS = 5};
class Milight: public ProgrammableLight
{
    public: 
    NetworkPacketSender UDPPacketSender;
    CanUseByteForALLGROUPS CheckIfCanUseByteForALLGROUPS (const std::vector<std::pair<const int, Colour>*> Collection);
    Milight();
   
    void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
   
    void SetColourForCurrentGroups(const Colour OutputColour);
    void SpecificCommand(const Command command);
   
    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour);
    void RemoveColour(const Colour OutputColour);
    
    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups);
    MilightGroupIDs GetGroupEnum(int GroupNumber);
    uint8_t GetGroupHexByte(int GroupNumber);

    void SetColourForCurrentGroups(const uint8_t ColourPacket[]);
    void SetWhiteForCurrentGroups();
    void TurnCurrentGroupsOff();
    std::vector<uint8_t> CurrentGroupBytes;

    void SendHue (const Colour OutputColour);
    void SendBrightness (const Colour OutputColour);
    void SendGroupOn (MilightGroupIDs GroupID);
    void SendGroupOFF();
    
};