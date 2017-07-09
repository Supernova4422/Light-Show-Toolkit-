#ifndef LIGHT01
#define LIGHT01

#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
struct Colour
{
    int red;
    int blue;
    int green;
    int Brightness;
};

class ProgrammableLight
{
    public:  
        virtual void SetColourForCurrentGroups(const Colour OutputColour) = 0;
        virtual void EmitColour(const Colour OutputColour) = 0;
        void SetGroup(std::vector<int> Groups, CommandOperation Operation);
    private:
        std::map<int, Colour> AllGroups;
        std::vector<const int*> CurrentlySelectedGroups;
        Colour CurrentSelectedColour;

    
 
};



#endif