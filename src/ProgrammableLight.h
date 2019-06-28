#ifndef PROGRAMMABLELIGHT01
#define PROGRAMMABLELIGHT01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"
#include "Color_Combiner.cpp"
class ProgrammableLight
{
public:
  virtual void EmitColour(const Command CommandItem, const std::map<int, colour_combiner> ExpectedOutput) = 0;

  virtual void OnCurrentGroupsUpdate(const Command CommandItem, const std::map<int, colour_combiner> CurrentGroups) = 0;

  virtual void SpecificCommand(const Command command) = 0;
  virtual ~ProgrammableLight() = default;
};

#endif