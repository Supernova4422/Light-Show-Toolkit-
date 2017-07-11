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

ProgrammableLight::ProgrammableLight(const GroupManager &Manager)
{
    this->Manager = &Manager;
}

std::pair<const int, Colour> *ProgrammableLight::GetGroupByID(int ID)
{
    Colour empty;
    std::pair<const int, Colour> *Entry;
    //If ID already exists, that one is returned instead
    Entry = &*(AllGroups.insert(std::pair<int, Colour>(ID, empty)).first);
    return Entry;
}

void ProgrammableLight::AddColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
        GetGroupByID(*group)->second += OutputColour;
    }
}
void ProgrammableLight::RemoveColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
        GetGroupByID(*group)->second -= OutputColour;
    }
}
void ProgrammableLight::SetColour(const Colour OutputColour)
{
    for (const int *group : Manager->CurrentlySelectedGroups)
    {
        GetGroupByID(*group)->second = OutputColour;
    }
}
