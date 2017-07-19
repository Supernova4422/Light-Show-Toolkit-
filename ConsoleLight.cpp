#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>
#include "GroupManager.h"



void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}

bool PostedNewGroups = true;
std::vector<std::pair<const int, Colour>*>* CurrentGroupsPTR;

void ConsoleLight::OnCurrentGroupsUpdate(GroupManager& Manager) {
    PostedNewGroups = false;
    CurrentGroupsPTR = &(Manager.CurrentlySelectedGroups);
}

void ConsoleLight::SpecificCommand(const Command command){
    std::cout << command.value << std::endl;
}
void ConsoleLight::EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput) {
}

void ConsoleLight::AddColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const std::pair<const int, Colour>* group : *CurrentGroupsPTR) {
            std::cout << group->first << ", ";
        }
            std::cout << std::endl;
    }

    PostedNewGroups = true;

    std::cout << "ADDING R: " << (int)OutputColour.red << " G: " << (int)OutputColour.green <<  " B: " << (int)OutputColour.blue << " A: " <<  std::endl;
}
void ConsoleLight::SetColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        for (const std::pair<const int, Colour>* group : *CurrentGroupsPTR) {
            std::cout << group->first << ", ";
        }
        std::cout << std::endl;
    }
    
    PostedNewGroups = true;
    std::cout << "SETTING COLOR:";
    std::cout << " R: " << (int) OutputColour.red;
    std::cout << " G: " << (int) OutputColour.green; 
    std::cout << " B: " << (int) OutputColour.blue;
    std::cout << std::endl;
    
    std::cout << "SETTING COLOR:";
    std::cout << " H: " << (int) OutputColour.Hue;
    std::cout << " S: " << (int) OutputColour.Saturation; 
    std::cout << " B: " << (int) OutputColour.Brightness;
    std::cout << std::endl;
} 
void ConsoleLight::RemoveColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const std::pair<const int, Colour>* group : *CurrentGroupsPTR) {
            std::cout << group->first << ", ";
        }
            std::cout << std::endl;
    }
    
    PostedNewGroups = true;

    std::cout << "REMOVING R: " << (int) OutputColour.red << " G: " << (int)OutputColour.green <<  " B: " << (int)OutputColour.blue << " A: " <<   std::endl;
}


