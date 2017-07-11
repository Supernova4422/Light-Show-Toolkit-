#ifndef COLOUR01
#define COLOUR01
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>

struct Colour
{
    //TODO Make each a byte only, to limit values between 0-255
    int red = 0;
    int green = 0;
    int blue = 0;
    int Brightness = 0;
    Colour (std::string HexString);
    
    
    Colour();

    Colour operator+=(const Colour& c){
        this->red += c.red;
        this->green += c.green;
        this->blue += c.blue;
        this->Brightness += c.Brightness;
    }
    Colour operator-=(const Colour& c){
        this->red -= c.red;
        this->green -= c.green;
        this->blue -= c.blue;
        this->Brightness -= c.Brightness;
    }   
};
#endif