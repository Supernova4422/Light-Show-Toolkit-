#ifndef COLOUR01
#define COLOUR01
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>
#include <stdlib.h> 
#include <math.h> 
struct Colour
{
    Colour();
	//If true, the string is RGB
	//if false the string is HSB
    Colour (std::string HexString, const bool rgb);
    
    void UpdateHSBColours();
	void UpdateRGBColours();
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    
    uint8_t Hue = 0;
    uint8_t Saturation = 0;
    uint8_t Brightness = 0;
    
    void operator+=(const Colour& c){
        this->red += c.red;
        this->green += c.green;
        this->blue += c.blue;
        UpdateHSBColours();
    }
	void operator-=(const Colour& c){
        this->red -= c.red;
        this->green -= c.green;
        this->blue -= c.blue;
        UpdateHSBColours();
    } 
    private: 

};
#endif
