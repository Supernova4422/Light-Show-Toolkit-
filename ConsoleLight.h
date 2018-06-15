#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"

class ConsoleLight: public ProgrammableLight
{
    public: 
    ConsoleLight();
	
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
    void SpecificCommand(const Command command);

    void OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups);
	private: 
	bool PostedNewGroups = false;
};