#ifndef GROUPMANAGER_01
#define GROUPMANAGER_01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "ColourListiner.h"

class GroupManager: public ColourListiner
{
  public:
    void SetGroups(const int Group, CommandOperation Operation);
    void AddToCurrentGroups(const int GroupToAdd);
    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour); 
    void RemoveColour(const Colour OutputColour); 

    std::pair<const int, Colour> *GetGroupByID(const int ID);
    std::vector<const int *> CurrentlySelectedGroups;
  private:
    std::map<int, Colour> AllGroups;
    Colour CurrentSelectedColour;
    
};
#endif