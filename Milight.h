#include "CommandDataTypes.cpp"
#include "ProgrammableLight.h"


class Milight: public ProgrammableLight
{
    public: 
    void SetColourForCurrentGroups(const Colour OutputColour);
    void EmitColour(const Colour OutputColour); 
   
    void AddColour(const Colour OutputColour) = 0; 
    void SetColour(const Colour OutputColour) = 0;
    void RemoveColour(const Colour OutputColour) = 0;
    
    void OnCurrentGroupsUpdate();
};