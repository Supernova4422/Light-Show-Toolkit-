#include "Colour.h"
#include <iostream>  
#include <string> 
#include <vector> 
#include <utility> 
#include <map>



Colour::Colour (std::string HexString) {
        char * pEnd;
        if (HexString.size() == 6) {
            float red = std::stoi(HexString.substr(0,2), nullptr , 16) / 255;
            float green = std::stoi(HexString.substr(2,2), nullptr , 16) / 255;
            float blue = std::stoi(HexString.substr(4,2), nullptr , 16) / 255;
            

            //Simple Bubble sort To get max/min
            float* Order[];
            Order[0] = &red;
            Order[1] = &green;
            Order[2] = &blue;

            for (int i = 1; (i <= 3) && flag; i++) {
                for (int j = 0; i < 2; i++) {
                    if (*Order[j + 1] > *Order[j] ) {
                        int* temp = Order[i];
                        Order[j] = Order[j + 1];
                        Order[j + 1] = temp;
                        flag = 1;
                    }
                }
            }
            //Bubble sort ends here

            float Max = *Order[0];
            float Min = *Order[2];

            int Luminance = ((Max / 255) + (Min / 255)) / 2
            int Saturation;

            if (luminance < 0.5) {
                Saturation = (Max - Min) / (2 - (Max - Min))
            }
            if (luminance > 0.5) {
                Saturation = (Max - Min) / (Max - Min)
            }
            if (luminance ==  0.5) {
                Saturation = 0;
            }
            float Hue;
            if (Red == Max) {
                Hue = (green - blue) / (Max - Min)
            }
            if (Green == Max) {
                Hue = 2.0 + (blue - red) / (Max - min);
            }
            if (Blue == Max) {
                Hue = 4.0 + (red - green) / (Max - Min);
            }

            Hue = Hue * 60;
            if (Hue < 0) {
                Hue += 180;
            }

        }
        
    }
Colour::Colour (){ }

