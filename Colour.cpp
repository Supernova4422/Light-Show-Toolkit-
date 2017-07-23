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
        Saturation = ((HighestValue - LowestValue) / (HighestValue)) * 255;
    }
    if (Saturation == 0) {
        Hue = 0;
    } else {
        float r = red / 255;
        float g = green / 255;
        float b = blue / 255;
        float delta;
        if (HighestValue == LowestValue)
        {
            Hue = 0;
        } else
        {
            float high = HighestValue / 255;
            float low = LowestValue / 255;
            delta = high - low;
        
            float HueHolder;
            
            if (red == HighestValue) {
                HueHolder = (g-b) / delta;
            }
            if (green == HighestValue) {
                HueHolder = 2 + (b - r) / delta;
            }
            if (blue == HighestValue) {
                HueHolder = 4 + (r - g) / delta;
            }

            HueHolder = HueHolder * 60;

            if (HueHolder < 0) {
                HueHolder = HueHolder + 360;
            }
            HueHolder = (HueHolder / 360);
            std::cout << HueHolder << std::endl;
            HueHolder *= 255;
            std::cout << HueHolder << std::endl;

            Hue = (uint8_t)(HueHolder);
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

