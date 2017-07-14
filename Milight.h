#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"

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
    void SendHexPackets (char buffer[]);
};