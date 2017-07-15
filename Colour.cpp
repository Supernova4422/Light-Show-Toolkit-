#include "Colour.h"
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>
#include <algorithm> 

std::array<float,3> Colour::GetOrderedAndScaledRGB() {
    int flag;
    //Simple Bubble sort To get max/min
    std::array<float,3> Order;
    Order[0] = (float)red;// / 255; //&red;
    Order[1] = (float)green;// / 255; //&green;
    Order[2] = (float)blue;// / 255; //&blue;

    std::cout <<  "RED IS: " << Order[0] << std::endl;

    for (int i = 1; (i <= 3) && flag; i++) {
        for (int j = 0; i < 2; i++) {
            if (Order[j + 1] > Order[j] ) {
                float temp = Order[i];
                Order[j] = Order[j + 1];
                Order[j + 1] = temp;
                flag = 1;
            }
        }
    }
    return Order;
}
void Colour::UpdateHSBColours () {
    std::array<float,3> ScaledOrderedRGB;
    ScaledOrderedRGB = GetOrderedAndScaledRGB();
    float HighestValue = std::max(std::max(red,green),blue);
    float LowestValue = std::min(std::min(red,green),blue);

    
    std::cout <<  (int)blue << std::endl;
    std::cout <<  (int)HighestValue << std::endl;

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

    std::cout <<  "HUE IS: " << (int)Hue << std::endl;
    if (Hue < 0) {
       // Hue += 180;
    }
    
}

Colour::Colour (std::string HexString) {
        red = (uint8_t) std::stoi(HexString.substr(0,2), nullptr , 16);
        green = (uint8_t) std::stoi(HexString.substr(2,2), nullptr , 16);
        blue = (uint8_t) std::stoi(HexString.substr(4,2), nullptr , 16);
        UpdateHSBColours();
}
Colour::Colour (){ }

