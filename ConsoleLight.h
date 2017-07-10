#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"

class ConsoleLight: public ProgrammableLight
{
    public: 
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour);

    void AddColour(const Colour OutputColour); 
    void SetColour(const Colour OutputColour); 
    void RemoveColour(const Colour OutputColour); 

    void OnCurrentGroupsUpdate();
};