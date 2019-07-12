#include "Command.h"
#include "ConsoleLight.h"
#include <iostream>
#include "GroupManager.h"

int ConsoleLight::count = 0;

void ConsoleLight::EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput)
{
    std::cout << label << ":" << std::endl;
    if (PostedNewGroups == false)
    {
        std::cout << "Sending to groups: ";

        for (auto group : ExpectedOutput)
        {
            std::cout << group.first << ", ";
        }
        std::cout << std::endl;

        PostedNewGroups = true;
    }

    Colour NewColour(CommandItem.value, CommandItem.type == ColourChange_RGB);

    switch (CommandItem.Operation)
    {
    case set:
        std::cout << "Set: ";
        break;
    case add:
        std::cout << "Add: ";
        break;
    case Remove:
        std::cout << "Remove: ";
        break;
    }

    std::cout << "R: " << (int)NewColour.red << " G: " << (int)NewColour.green << " B: " << (int)NewColour.blue << std::endl;

    std::cout
        << "H: " << (int)NewColour.Hue
        << " S: " << (int)NewColour.Saturation
        << " B: " << (int)NewColour.Brightness
        << std::endl;

    if (wait > 0)
    {
        std::cout << "Pausing Thread... " << label << std::endl;
        std::this_thread::sleep_for(std::chrono::seconds((int)wait));
        std::cout << " Finished waiting on thread: " << label << std::endl;
    }

    std::cout << std::endl;
    std::cout << std::endl;
}

void ConsoleLight::OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, Colour_Combiner> CurrentGroups)
{
    PostedNewGroups = false;
}

void ConsoleLight::SpecificCommand(const Command command, const std::map<int, Colour_Combiner> CurrentGroups)
{
    std::cout << "Specific Command: " << command.value << std::endl;
}
