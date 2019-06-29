#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"
#include "GroupManager.h"

class ConsoleLight : public ProgrammableLight
{
public:
    ConsoleLight();

    void SetColourForCurrentGroups(const Colour OutputColour,
                                   const std::map<int, colour_combiner> CurrentGroups);
    void EmitColour(const Command CommandItem,
                    const std::map<int, colour_combiner> ExpectedOutput) override ;

    void SpecificCommand(const Command command,
                         const std::map<int, colour_combiner> CurrentGroups) override;

    void OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, colour_combiner> CurrentGroups) override;

    void OnStart() override {};
    void OnEnd() override {};
private:
    bool PostedNewGroups = false;
};