#ifndef COLOUR01
#define COLOUR01
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>

struct Colour
{
    Colour();
    Colour (std::string HexString);
    
    void UpdateHSLColours();
     //TODO Make each a byte only, to limit values between 0-255
    int red = 0;
    int green = 0;
    int blue = 0;
    
    int Hue = 0;
    int Saturation = 0;
    int Luminance = 0;
    
    Colour operator+=(const Colour& c){
        this->red += c.red;
        this->green += c.green;
        this->blue += c.blue;
        UpdateHSLColours();
    }
    Colour operator-=(const Colour& c){
        this->red -= c.red;
        this->green -= c.green;
        this->blue -= c.blue;
        UpdateHSLColours();
    } 
    private: 

   

    std::array<float,3> GetOrderedAndScaledRGB ();

    //DO HSL IN HERE  
};
#endif
