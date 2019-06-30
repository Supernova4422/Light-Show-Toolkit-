#pragma once

#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"

class ConsoleLight : public ProgrammableLight
{
public:

    ConsoleLight(std::string label = std::string("DEFAULT_") + std::to_string(ConsoleLight::count), const size_t delay = 0) : label(label),  delay(delay)
    {
        count += 1;
        std::cout << "All commands will print to console" << std::endl;
    };

    void SetColourForCurrentGroups(const Colour OutputColour,
                                   const std::map<int, colour_combiner> CurrentGroups);
    void EmitColour(const Command CommandItem,
                    const std::map<int, colour_combiner> ExpectedOutput) override ;

    void SpecificCommand(const Command command,
                         const std::map<int, colour_combiner> CurrentGroups) override;

    void OnCurrentGroupsUpdate(const Command CommandItem,
                        const std::map<int, colour_combiner> CurrentGroups) override;

    void OnStart() override {
        std::cout << "Starting: " << label << std::endl;
    };
    void OnEnd() override {
        std::cout << "Ending: " << label << std::endl;
    };
private:
    bool PostedNewGroups = false;
    size_t delay;
    std::string label;
    static int count;
};

