#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"

class ConsoleLight: public ProgrammableLight
{
    public:
    ConsoleLight();

    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Command CommandItem , const std::map<int, colour_combiner> ExpectedOutput);
    void SpecificCommand(const Command command);

    void OnCurrentGroupsUpdate(const Command CommandItem , std::map<int, colour_combiner>  CurrentGroups);
	private:
	bool PostedNewGroups = false;
};