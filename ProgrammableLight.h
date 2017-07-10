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
    //TODO Make each a byte only, to limit values between 0-255
    int red = 0;
    int green = 0;
    int blue = 0;
    int Brightness = 0;
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

    Colour operator+=(const Colour& c) {
        this->red += c.red;
        this->green += c.green;
        this->blue += c.blue;
        this->Brightness += c.Brightness;
    }
    Colour operator-=(const Colour& c) {
        this->red -= c.red;
        this->green -= c.green;
        this->blue -= c.blue;
        this->Brightness -= c.Brightness;
    }

};

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