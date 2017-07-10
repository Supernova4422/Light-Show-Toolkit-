#include "Colour.h"
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>



Colour::Colour (std::string HexString) {
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
Colour::Colour (){ }

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
    

