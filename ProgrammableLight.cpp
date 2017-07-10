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

void ProgrammableLight::SetGroups(const int Group, CommandOperation Operation)
{
   
    Colour empty;
    std::pair<std::map<int,Colour>::iterator,bool> ret;
    std::pair<const int,Colour>* Entry;
    const int* PointerToGroupID;
    
    switch (Operation) {
        case set :
            CurrentlySelectedGroups.clear();
            AddToCurrentGroups(Group);
        break;
        case add :
            AddToCurrentGroups(Group);
        break; 
        case Remove :
        //This hasn't been done now as this function will not likely see usage
              
        std::pair<const int,Colour>* Entry = GetGroupByID(Group);
                
        //A pointer is used to ensure that the group is kept track of
        PointerToGroupID = &Entry->first;

        CurrentlySelectedGroups.erase( std::remove(CurrentlySelectedGroups.begin(),
                                            CurrentlySelectedGroups.end(),
                                            PointerToGroupID),CurrentlySelectedGroups.end());
         
        break;
    }

    OnCurrentGroupsUpdate();
    
}
void ProgrammableLight::AddToCurrentGroups(const int GroupToAdd) {
    Colour empty;
    std::pair<const int,Colour>* Entry = GetGroupByID(GroupToAdd);
    //A pointer is used to ensure that the group is kept track of
    const int* PointerToGroupID = &Entry->first;
    CurrentlySelectedGroups.push_back(PointerToGroupID);
}

std::pair<const int,Colour>* ProgrammableLight::GetGroupByID (int ID) {
    Colour empty;
    std::pair<const int,Colour>* Entry;
    //If ID already exists, that one is returned instead
    Entry = &*( AllGroups.insert  (std::pair<int,Colour> (ID, empty)).first);
    return Entry;
}

void ProgrammableLight::AddColour(const Colour OutputColour) {
    for (const int* group : CurrentlySelectedGroups) {
        GetGroupByID(*group)->second += OutputColour;
    }
}
void ProgrammableLight::RemoveColour(const Colour OutputColour) {
    for (const int* group : CurrentlySelectedGroups) {
        GetGroupByID(*group)->second -= OutputColour;
    }
}
void ProgrammableLight::SetColour(const Colour OutputColour) {
    for (const int* group : CurrentlySelectedGroups) {
        GetGroupByID(*group)->second = OutputColour;
    }
}
