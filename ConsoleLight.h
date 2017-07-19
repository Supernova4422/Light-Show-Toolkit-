#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"

class ConsoleLight: public ProgrammableLight
{
    public: 
    ConsoleLight() : ProgrammableLight(){};

    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
    void SpecificCommand(const Command command);
    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour); 
    void RemoveColour(const Colour OutputColour); 

    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups);
};