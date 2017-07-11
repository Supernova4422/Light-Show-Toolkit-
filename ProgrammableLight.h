#ifndef PROGRAMMABLELIGHT01
#define PROGRAMMABLELIGHT01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "ColourListiner.h"
#include "GroupManager.h"
class ProgrammableLight: public ColourListiner
{
  public:
    
    virtual void EmitColour(const Colour OutputColour) = 0;

    virtual void OnCurrentGroupsUpdate() = 0;
    
    void SetGroups(const int Group, CommandOperation Operation);
    void AddToCurrentGroups(const int GroupToAdd);
    
    void AddColour(const Colour OutputColour);
    void SetColour(const Colour OutputColour);
    void RemoveColour(const Colour OutputColour);

    ProgrammableLight(const GroupManager& Manager);
    const GroupManager* Manager;

  private:
    std::map<int, Colour> AllGroups;
    Colour CurrentSelectedColour;
    std::pair<const int, Colour> *GetGroupByID(int ID);
};

#endif