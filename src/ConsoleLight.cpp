#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>
#include "GroupManager.h"


ConsoleLight::ConsoleLight() {
    std::cout << "All commands will print to console" << std::endl;
    std::cout << std::endl;
}

void ConsoleLight::EmitColour(const Command CommandItem , const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput) {

    if (PostedNewGroups == false)
    {
        std::cout << "Sending to groups: ";

        for (const std::pair<const int, colour_combiner>* group : ExpectedOutput) {
            std::cout << group->first << ", ";
        }

        PostedNewGroups = true;

        std::cout << std::endl;
    }
    
    Colour NewColour(CommandItem.value , CommandItem.type == ColourChange_RGB);
    
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
    
    std::cout << "R: " << (int) NewColour.red << " G: " << (int) NewColour.green << " B: " << (int) NewColour.blue << std::endl;
    std::cout << "H: " << (int) NewColour.Hue << " S: " << (int) NewColour.Saturation << " B: " << (int) NewColour.Brightness << std::endl;
    std::cout << std::endl;
	
}

void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}




void ConsoleLight::OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, colour_combiner>*>  CurrentGroups) {
    PostedNewGroups = false;
}

void ConsoleLight::SpecificCommand(const Command command){
    std::cout << command.value << std::endl;
}


