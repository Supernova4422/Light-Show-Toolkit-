#pragma once
#include "ProgrammableLight.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <errno.h>
#include "BinaryLightController.h"
#include "Colour_Combiner.cpp"
#include "ProxyMaker.h"
#include <vector>
#include <set>

template <class T>
class BinaryLight : public ProgrammableLight
{
public:
	BinaryLight(int upperlimit = 1, int group_offset = 0) : threshhold(upperlimit), group_offset(group_offset), light()
	{
		std::cout << std::endl
				  << "Binary Light loaded" << std::endl;
		std::cout << "All commands will print to console, focusing on turning off and on" << std::endl;
		std::cout << "Upper limit set to: " << upperlimit << std::endl;
		proxies = ProxyMaker::proxy_filereader("proxy_binarylight.txt");

		light.initialise();
	};

	void SetColourForCurrentGroups(const Colour OutputColour){};
	void SpecificCommand(const Command command){};

	void EmitColour(const Command CommandItem, const std::map<int, Colour_Combiner> ExpectedOutput)
	{
		auto proxiedOutput = ProxyMaker::proxy_maker(ExpectedOutput, proxies);
		for (auto pair : proxiedOutput)
		{
			int group = pair.first + group_offset;
			bool shouldturnon = (pair.second.get_colour().Brightness > threshhold);
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

private:
	std::map<std::set<int>, int, cmpBySetSize> proxies;
	T light;
	unsigned int threshhold = 0;
	int group_offset = 0;
};
