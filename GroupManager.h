#ifndef GROUPMANAGER_01
#define GROUPMANAGER_01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "ProgrammableLight.h"
class GroupManager
{
  public:
    void SetGroups(const int Group, Command CommandItem);
    void AddToCurrentGroups(const int GroupToAdd);
    void AddColour(const Colour OutputColour , Command item); 
    void SetColour(const Colour OutputColour , Command item); 
    void RemoveColour(const Colour OutputColour , Command item); 
    void SpecificCommand(const Command command);
    
    GroupManager();
    
    std::pair<const int, Colour> *GetGroupByID(const int ID);
    std::vector<std::pair<const int, Colour>*> CurrentlySelectedGroups;
  private:
    std::map<int, Colour> AllGroups;
    Colour CurrentSelectedColour;
    std::vector<ProgrammableLight*> ListeningLights;
    
};
#endif