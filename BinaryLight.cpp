#include <stdint.h>

#include "BinaryLight.h"

void BinaryLight::EmitColour(const Command CommandItem, const std::vector<std::pair<const int, Colour>*> ExpectedOutput)
{
	for (auto pair : ExpectedOutput)
	{
		int group = pair->first;
		bool shouldturnon = (pair->second.Brightness > threshhold);
		std::cout << "Group: " << group << " will be made " << shouldturnon << std::endl;
		
		if (shouldturnon)
		{
			light->turnon(group);
		}
		else
		{
			light->turnoff(group);
		}
		
	}
	std::cout << std::endl;
}
