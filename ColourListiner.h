#ifndef COLOURLISTINER01
#define COLOURLISTINER01
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"

class ColourListiner
{
  public:
    virtual void EmitColour(const Command CommandItem , const std::vector<std::pair<const int, Colour>*> ExpectedOutput) = 0;
};
#endif