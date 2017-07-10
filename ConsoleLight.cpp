#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>


void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}

bool PostedNewGroups = false;

void ConsoleLight::OnCurrentGroupsUpdate() {
    PostedNewGroups = false;
}

void ConsoleLight::EmitColour(const Colour OutputColour) {
    
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const int* group : CurrentlySelectedGroups) {
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
        
        for (const int* group : CurrentlySelectedGroups) {
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
        
        for (const int* group : CurrentlySelectedGroups) {
            std::cout << *group << ", ";
        }
            std::cout << std::endl;
    }
    
    PostedNewGroups = true;

    std::cout << "REMOVING R: " << OutputColour.red << " G: " << OutputColour.green <<  " B: " << OutputColour.blue << " A: " << OutputColour.Brightness <<  std::endl;
}


