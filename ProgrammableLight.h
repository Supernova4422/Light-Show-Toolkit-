#ifndef LIGHT01
#define LIGHT01
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"

struct Colour
{
    int red;
    int green;
    int blue;
    int Brightness;
    Colour (std::string HexString) {
        char * pEnd;
        if (HexString.size() == 2) {
             this->Brightness = std::stoi(HexString.substr(0,2), nullptr , 16);
        } else if (HexString.size() >= 6) {
            this->red = std::stoi(HexString.substr(0,2), nullptr , 16);
            this->green = std::stoi(HexString.substr(2,2), nullptr , 16);
            this->blue = std::stoi(HexString.substr(4,2), nullptr , 16);
        }
        if (HexString.size() >= 8) {
            this->Brightness = std::stoi(HexString.substr(6,2), nullptr , 16);
        }
    }
    Colour (){ }
};

class ProgrammableLight
{
    public:  
        virtual void SetColourForCurrentGroups(const Colour OutputColour) = 0;
        virtual void EmitColour(const Colour OutputColour) = 0;
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