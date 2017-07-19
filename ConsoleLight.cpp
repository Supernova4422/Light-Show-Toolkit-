#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>
#include "GroupManager.h"
bool PostedNewGroups = true;
void ConsoleLight::EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput) {

    
    if (PostedNewGroups == false)
    {
        std::cout << "CURRENT GROUPS:" << std::endl;
        for (const std::pair<const int, Colour>* group : ExpectedOutput) {
            std::cout << group->first << ", ";
        }
        PostedNewGroups = true;
    }
    
    
    std::cout << std::endl;

    Colour NewColour(CommandItem.value);
    
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
    
    std::cout << "R: " << (int) NewColour.red << " G: " << NewColour.green << " B: " << NewColour.blue << std::endl;
    std::cout << "H: " << (int) NewColour.Hue << " S: " << NewColour.Saturation << " B: " << NewColour.Brightness << std::endl;
}

void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}




void ConsoleLight::OnCurrentGroupsUpdate(const Command CommandItem , std::vector<std::pair<const int, Colour>*>  CurrentGroups) {
    PostedNewGroups = false;
}

void ConsoleLight::SpecificCommand(const Command command){
    std::cout << command.value << std::endl;
}


