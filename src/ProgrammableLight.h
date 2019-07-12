#ifndef PROGRAMMABLELIGHT01
#define PROGRAMMABLELIGHT01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "Command.h"
#include "Colour.h"
#include "Colour_Combiner.cpp"
class ProgrammableLight
{
public:
  virtual void EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput) = 0;

  virtual void OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, Colour_Combiner> CurrentGroups) = 0;

  virtual void SpecificCommand(const Command command, const std::map<int, Colour_Combiner> CurrentGroups) = 0;

  virtual void OnStart() = 0;
  virtual void OnEnd() = 0;

  virtual ~ProgrammableLight() = default;
};

#endif