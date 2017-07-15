#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>
#include "GroupManager.h"



void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}

bool PostedNewGroups = true;
std::vector<const int*>* CurrentGroupsPTR;

void ConsoleLight::OnCurrentGroupsUpdate(GroupManager& Manager) {
    PostedNewGroups = false;
    CurrentGroupsPTR = &(Manager.CurrentlySelectedGroups);
}

void ConsoleLight::SpecificCommand(const Command command){
    std::cout << command.value << std::endl;
}

void ConsoleLight::EmitColour(const Colour OutputColour) {
    
    if (PostedNewGroups == false) {
        for (const int* group : *CurrentGroupsPTR) {
            std::cout << *group << ", ";
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

void ConsoleLight::AddColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const int* group : *CurrentGroupsPTR) {
            std::cout << *group << ", ";
        }
            std::cout << std::endl;
    }

    PostedNewGroups = true;

    std::cout << "ADDING R: " << (int)OutputColour.red << " G: " << (int)OutputColour.green <<  " B: " << (int)OutputColour.blue << " A: " <<  std::endl;
}
void ConsoleLight::SetColour(const Colour OutputColour) {
    EmitColour(OutputColour);
} 
void ConsoleLight::RemoveColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const int* group : *CurrentGroupsPTR) {
            std::cout << *group << ", ";
        }
            std::cout << std::endl;
    }
    
    PostedNewGroups = true;

    std::cout << "REMOVING R: " << (int) OutputColour.red << " G: " << (int)OutputColour.green <<  " B: " << (int)OutputColour.blue << " A: " <<   std::endl;
}


