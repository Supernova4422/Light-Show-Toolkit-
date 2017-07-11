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

void ConsoleLight::EmitColour(const Colour OutputColour) {
    
    if (PostedNewGroups == false) {
        
        
        for (const int* group : *CurrentGroupsPTR) {
            std::cout << *group << ", ";
        }
        std::cout << std::endl;
    }
    
    PostedNewGroups = true;

    std::cout << "SETTING COLOR: R: " << OutputColour.red << " G: " << OutputColour.green <<  " B: " << OutputColour.blue << " A: " << OutputColour.Brightness <<  std::endl;
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

    std::cout << "ADDING R: " << OutputColour.red << " G: " << OutputColour.green <<  " B: " << OutputColour.blue << " A: " << OutputColour.Brightness <<  std::endl;
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

    std::cout << "REMOVING R: " << OutputColour.red << " G: " << OutputColour.green <<  " B: " << OutputColour.blue << " A: " << OutputColour.Brightness <<  std::endl;
}


