#include "Colour.h"
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>


std::array<float,3> Colour::GetOrderedAndScaledRGB() {
    int flag;
    //Simple Bubble sort To get max/min
    std::array<float,3> Order;
    Order[0] = (int)red / 255; //&red;
    Order[1] = (int)green / 255; //&green;
    Order[2] = (int)blue / 255; //&blue;

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
void Colour::UpdateHSLColours () {
    std::array<float,3> ScaledOrderedRGB;
    ScaledOrderedRGB = GetOrderedAndScaledRGB();

    float Max = ScaledOrderedRGB[0];
    float Min = ScaledOrderedRGB[2];

    Luminance = (Max + Min) / 2;
    

    if (Luminance < 0.5) {
        Saturation = (Max - Min) / (2 - (Max - Min));
    }
    if (Luminance > 0.5) {
        Saturation = (Max - Min) / (Max - Min);
    }
    if (Luminance ==  0.5) {
        Saturation = 0;
    }
    
    if (red == Max) {
        Hue =  (green  - blue   ) / (Max - Min);
    }
    if (green == Max) {
        Hue = 2.0 + (blue - red ) / (Max - Min);
    }
    if (blue == Max) {
        Hue = 4.0 + (red - green ) / (Max - Min);
    }

    Hue = Hue * 60;
    if (Hue < 0) {
        Hue += 180;
    }
}

Colour::Colour (std::string HexString) {
        red = (uint8_t) std::stoi(HexString.substr(0,2), nullptr , 16);
        green = (uint8_t) std::stoi(HexString.substr(2,2), nullptr , 16);
        blue = (uint8_t) std::stoi(HexString.substr(4,2), nullptr , 16);
}
Colour::Colour (){ }

