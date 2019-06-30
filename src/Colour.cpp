#include "Colour.h"
#include <iostream>
#include <string>
#include <vector>
#include <utility>
#include <map>
#include <algorithm>

void Colour::UpdateHSBColours()
{

	float HighestValue = std::max(std::max(red, green), blue);
	float LowestValue = std::min(std::min(red, green), blue);

	Brightness = HighestValue;
	if (HighestValue == 0)
	{
		Saturation = 0;
	}
	else
	{
		Saturation = ((HighestValue - LowestValue) / (HighestValue)) * 255;
	}
	if (Saturation == 0)
	{
		Hue = 0;
	}
	else
	{
		float r = (float)red / 255;
		float g = (float)green / 255;
		float b = (float)blue / 255;
		float delta;
		if (HighestValue == LowestValue)
		{
			Hue = 0;
		}
		else
		{
			float high = HighestValue / 255;
			float low = LowestValue / 255;
			delta = high - low;

			float HueHolder = 0.0f;

			if (red == HighestValue)
			{
				HueHolder = (g - b) / delta;
			}
			else if (green == HighestValue)
			{
				HueHolder = 2 + (b - r) / delta;
			}
			else if (blue == HighestValue)
			{
				HueHolder = 4 + (r - g) / delta;
			}

			HueHolder = HueHolder * 60;

			if (HueHolder < 0)
			{
				HueHolder = HueHolder + 360;
			}
			HueHolder = (HueHolder / 360);
			HueHolder *= 255;

			Hue = (uint8_t)(HueHolder);
		}
	}
}

void Colour::UpdateRGBColours()
{
	float hue_resized = float(Hue) * (360.0F / 255.0F);
	float sat_resized = float(Saturation) / 255.0f;
	float b_resized = float(Brightness) / 255.0f;

	double chroma = b_resized * sat_resized;
	double x = chroma * (1.0f -
						 abs(
							 (
								 fmod(hue_resized / 60.0f, 2) - 1.0f)));

	float m = b_resized - chroma;

	if (0 <= hue_resized && hue_resized <= 60)
	{
		red = (chroma + m) * 255;
		green = (x + m) * 255;
		blue = m * 255;
	}
	else if (60 <= hue_resized && hue_resized <= 120)
	{
		red = (x + m) * 255;
		green = (chroma + m) * 255;
		blue = m * 255;
	}
	else if (120 <= hue_resized && hue_resized <= 180)
	{
		red = m * 255;
		green = (chroma + m) * 255;
		blue = (x + m) * 255;
	}
	else if (180 <= hue_resized && hue_resized <= 240)
	{
		red = m * 255;
		green = (x + m) * 255;
		blue = (chroma + m) * 255;
	}
	else if (240 <= hue_resized && hue_resized <= 300)
	{
		red = (x + m) * 255;
		green = m * 255;
		blue = (chroma + m) * 255;
	}
	else if (300 <= hue_resized && hue_resized <= 360)
	{
		red = (chroma + m) * 255;
		green = m * 255;
		blue = (x + m) * 255;
	}
}
