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
    bool rgb_built = false; //This is important for the += and -= section to work, read that more
    void UpdateHSBColours();
	void UpdateRGBColours();
    uint8_t red = 0;
    uint8_t green = 0;
    uint8_t blue = 0;
    
    uint8_t Hue = 0;
    uint8_t Saturation = 0;
    uint8_t Brightness = 0;
    
    //This is done to ensure that #270000 and #270000 will add 27 to red both times, whilst allowing
    //$600000 +$600000 to add 60 to the Hue.
    
    void operator+=(const Colour& c){
        if (c.rgb_built)
        {
            this->red += c.red;
            this->blue += c.blue;
            this->green += c.green;
            UpdateHSBColours();
        } else {
            this->Hue += c.Hue;
            this->Saturation += c.Saturation;
            this->Brightness += c.Brightness;
            UpdateRGBColours();
        }
    }
	void operator-=(const Colour& c){
        if (c.rgb_built){
            this->red -= c.red;
            this->blue -= c.blue;
            this->green -= c.green;
            UpdateHSBColours();
        } else {
            this->Hue -= c.Hue;
            this->Saturation -= c.Saturation;
            this->Brightness -= c.Brightness;
            UpdateRGBColours();
        }
    }
    
    private: 

};
#endif
