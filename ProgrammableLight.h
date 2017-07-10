#ifndef PROGRAMMABLELIGHT01
#define PROGRAMMABLELIGHT01
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
#include "Colour.h"


class ProgrammableLight
{
    public:  
        virtual void SetColourForCurrentGroups(const Colour OutputColour) = 0;
        void EmitColour(const Colour OutputColour);
        
        virtual void AddColour(const Colour OutputColour) = 0; 
        virtual void SetColour(const Colour OutputColour) = 0;
        virtual void RemoveColour(const Colour OutputColour) = 0;

        virtual void OnCurrentGroupsUpdate() = 0;
        void SetGroups(const int Group, CommandOperation Operation);
        void AddToCurrentGroups(const int GroupToAdd);
        std::vector<const int*> CurrentlySelectedGroups;
        
    private:
        std::map<int, Colour> AllGroups;
        Colour CurrentSelectedColour;
        std::pair<const int,Colour>* GetGroupByID (int ID);

};

#endif