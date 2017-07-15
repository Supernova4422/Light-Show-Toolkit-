#include "Colour.h"
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>
#include <algorithm> 


void Colour::UpdateHSBColours () {
    
    float HighestValue = std::max(std::max(red,green),blue);
    float LowestValue = std::min(std::min(red,green),blue);

    
    
    Brightness = HighestValue;
    if (HighestValue == 0) {
        Saturation = 0;
    } else {
        Saturation = (HighestValue - LowestValue) / (HighestValue);
    }
    if (Saturation == 0) {
        Hue = 0;
    } else {
        if (red == HighestValue) {
            Hue =  ((green  - blue) / (HighestValue - LowestValue) ) * 60 / 360 * 255;
        }
        if (green == HighestValue) {
            
            Hue = ( 2.0 +   ((blue - red ) / 255) / ((HighestValue - LowestValue) / 255))  * 60 / 360 * 255;
        }
        if (blue == HighestValue) {
            float data = (4.0 + (( (red - green ) / 255) / ((HighestValue - LowestValue) / 255))) * 60 / 360 * 255;

            Hue = (4.0 + (( (red - green ) / 255) / ((HighestValue - LowestValue) / 255))) * 60 / 360 * 255;
           
        }
    }

    
}

Colour::Colour (std::string HexString) {
        red = (uint8_t) std::stoi(HexString.substr(0,2), nullptr , 16);
        green = (uint8_t) std::stoi(HexString.substr(2,2), nullptr , 16);
        blue = (uint8_t) std::stoi(HexString.substr(4,2), nullptr , 16);
        UpdateHSBColours();
}
Colour::Colour (){ }

