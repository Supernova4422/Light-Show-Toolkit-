#include "ProgrammableLight.h"
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include <algorithm>
#include <string>
#include <iostream>
#include <cctype>
#include "Colour.h"

ProgrammableLight::ProgrammableLight(GroupManager &Manager)
{
    this->Manager = &Manager;
}


void ProgrammableLight::AddColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
        Manager->GetGroupByID(*group)->second += OutputColour;
    }
}
void ProgrammableLight::RemoveColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
         Manager->GetGroupByID(*group)->second -= OutputColour;
    }
}
void ProgrammableLight::SetColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
         Manager->GetGroupByID(*group)->second = OutputColour;
    }
}
