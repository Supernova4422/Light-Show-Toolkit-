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
    virtual void OnCurrentGroupsUpdate(GroupManager& Manager) = 0;
    virtual void SpecificCommand(const Command command) = 0;

    void AddColour(const Colour OutputColour);
    void SetColour(const Colour OutputColour);
    void RemoveColour(const Colour OutputColour);

    ProgrammableLight(GroupManager& Manager);
    GroupManager* Manager;

    

  private:
   
};

#endif