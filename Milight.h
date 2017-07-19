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

class Milight: public ProgrammableLight
{
    public: 
    NetworkPacketSender UDPPacketSender;
    CanUseByteForALLGROUPS CheckIfCanUseByteForALLGROUPS (const std::vector<std::pair<const int, Colour>*> Collection);
    Milight() : ProgrammableLight(){};
   
    void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
   
    void SetColourForCurrentGroups(const Colour OutputColour);
    void SpecificCommand(const Command command);
   
    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour);
    void RemoveColour(const Colour OutputColour);
    
    void OnCurrentGroupsUpdate(GroupManager& Manager);

    char GetGroupHexByte(int GroupNumber);

    void SetColourForCurrentGroups(const char ColourPacket[]);
    void SetWhiteForCurrentGroups();
    void TurnCurrentGroupsOff();
    std::vector<char> CurrentGroupBytes;

    void SendHue(const Colour OutputColour, const char CurrentGroupByte);
    void SendBrightness(const Colour OutputColour, const char CurrentGroupByte);

    
};