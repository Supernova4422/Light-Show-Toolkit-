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
void ProgrammableLight::SetGroup(const std::vector<int> Groups, CommandOperation Operation)
{
   
    Colour empty;
    std::pair<std::map<int,Colour>::iterator,bool> ret;
    std::pair<const int,Colour>* Entry;
    const int* PointerToGroupID;
    
    switch (Operation) {
        case set :
            CurrentlySelectedGroups.clear();
            AddToCurrentGroups(Groups);
        break;
        case add :
            AddToCurrentGroups(Groups);
        break; 
        case Remove :
        //This hasn't been done now as this function will not likely see usage
            for (int group : Groups) {
               
                std::pair<const int,Colour>* Entry = GetGroupByID(group);
                
                //A pointer is used to ensure that the group is kept track of
                PointerToGroupID = &Entry->first;

                CurrentlySelectedGroups.erase(std::remove(CurrentlySelectedGroups.begin(),
                                                        CurrentlySelectedGroups.end(),
                                                        PointerToGroupID),CurrentlySelectedGroups.end());
            } 
        break;
        default :
        break;
    }
    
}
void ProgrammableLight::AddToCurrentGroups(const std::vector<int> GroupsToAdd) {
    Colour empty;
    
    for (int group : GroupsToAdd) {
                std::pair<const int,Colour>* Entry = GetGroupByID(group);
                //A pointer is used to ensure that the group is kept track of
                const int* PointerToGroupID = &Entry->first;
                CurrentlySelectedGroups.push_back(PointerToGroupID);
    }

}

std::pair<const int,Colour>* ProgrammableLight::GetGroupByID (int ID) {
    Colour empty;
    std::pair<const int,Colour>* Entry;
    //If ID already exists, that one is returned instead
    Entry = &*( AllGroups.insert  (std::pair<int,Colour> (ID, empty)).first);
    return Entry;
}