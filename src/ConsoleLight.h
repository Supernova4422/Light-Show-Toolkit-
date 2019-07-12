#pragma once

#include "Command.h"
#include "ProgrammableLight.h"

class ConsoleLight : public ProgrammableLight
{
public:
    ConsoleLight(std::string label = std::string("DEFAULT_") + std::to_string(ConsoleLight::count), const size_t wait = 0) : wait(wait), label(label)
    {
        count += 1;
        std::cout << "All commands will print to console" << std::endl;
    };

    void EmitColour(const Command CommandItem,
                    const std::map<int, Colour_Combiner> ExpectedOutput) override;

    void SpecificCommand(const Command command,
                         const std::map<int, Colour_Combiner> CurrentGroups) override;

    void OnCurrentGroupsUpdate(const Command CommandItem,
                               const std::map<int, Colour_Combiner> CurrentGroups) override;

    void OnStart() override
    {
        std::cout << "Starting: " << label << std::endl;
    };
    void OnEnd() override
    {
        std::cout << "Ending: " << label << std::endl;
    };

private:
    bool PostedNewGroups = false;
    size_t wait;
    std::string label;
    static int count;
};
