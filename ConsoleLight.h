#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"

class ConsoleLight: public ProgrammableLight
{
    public: 
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour); 
};