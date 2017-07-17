#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
#include <vector>
#include "NetworkPacketSender.h"
class Milight: public ProgrammableLight
{
    public: 
    NetworkPacketSender UDPPacketSender;

    Milight(GroupManager &Manager) : ProgrammableLight(Manager){};
   
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour); 
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
    
    
};