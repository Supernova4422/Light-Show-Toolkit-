#include "CommandDataTypes.cpp"
#include "ConsoleLight.h"
#include <iostream>


void ConsoleLight::SetColourForCurrentGroups(const Colour OutputColour) {
}

bool PostedNewGroups = false;

void ConsoleLight::EmitColour(const Colour OutputColour) {
    if (PostedNewGroups == false) {
        std::cout << "CURRENT GROUPS:" << std::endl;
        
        for (const int* group : CurrentlySelectedGroups) {
            std::cout << *group << std::endl;
        }
    }
    
    PostedNewGroups = true;

    std::cout << "SENDING COLOR: R: " << OutputColour.red << " G: " << OutputColour.green <<  " B: " << OutputColour.blue << " A: " << OutputColour.Brightness <<  std::endl;
}

void ConsoleLight::OnCurrentGroupsUpdate() {
    PostedNewGroups = false;
}