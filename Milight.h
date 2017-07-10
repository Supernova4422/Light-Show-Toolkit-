#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"

class Milight: public ProgrammableLight
{
    public: 
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour); 
    void OnCurrentGroupsUpdate();
};