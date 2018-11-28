#include <stdint.h>

#include "BinaryLight.h"
#include "Color_Combiner.cpp"

void BinaryLight::EmitColour(const Command CommandItem, const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput)
{
    auto proxiedOutput = ProxyMaker::proxy_maker(ExpectedOutput, proxies);
	for (auto pair : proxiedOutput)
	{
		//if (pair->second.brightness_changed()) {
			int group = pair->first + group_offset;
			bool shouldturnon = (pair->second.get_colour().Brightness > threshhold);
			std::cout << "Group: " << group << " will be made " << shouldturnon << std::endl;
			if (shouldturnon) {
				light->turnon(group);
			}
			else {
				light->turnoff(group);
			}
		//}
	}
	std::cout << std::endl;
}
