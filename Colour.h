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
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    
    uint8_t Hue = 0;
    uint8_t Saturation = 0;
    uint8_t Luminance = 0;
    
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
