#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"
#include <vector>
class Milight: public ProgrammableLight
{
    public: 
    Milight(GroupManager &Manager) : ProgrammableLight(Manager){};

    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour); 
    void SpecificCommand(const Command command);
   
    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour);
    void RemoveColour(const Colour OutputColour);
    
    void OnCurrentGroupsUpdate(GroupManager& Manager);

    void InitialiseUDPConnection (const char * IPAddress , unsigned short Port);
    void SendHexPackets (const char buffer[]);
    void SendHexPackets (const char buffer);

    char GetGroupHexByte(int GroupNumber);

    void SetColourForCurrentGroups(const char ColourPacket[]);
    void SetWhiteForCurrentGroups();
    std::vector<char> CurrentGroupBytes;
    
    
};