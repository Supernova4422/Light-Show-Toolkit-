#pragma once
#include "ProgrammableLight.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <errno.h>
#include "BinaryLightController.h"
#include "Color_Combiner.cpp"
#include "ProxyMaker.h"
#include <vector>
#include <set>
class BinaryLight : public ProgrammableLight
{
public:
	BinaryLight(BinaryLightController* light, int upperlimit = 1,  int group_offset = 0) : threshhold(upperlimit) , light(light), group_offset(group_offset) {
		std::cout << std::endl << "Binary Light loaded" << std::endl;
		std::cout << "All commands will print to console, focusing on turning off and on" << std::endl;
		std::cout << "Upper limit set to: " << upperlimit << std::endl;
        proxies = ProxyMaker::proxy_filereader("proxy_binarylight.txt");


		light->initialise();
	};

	void SetColourForCurrentGroups(const Colour OutputColour) {};
	void EmitColour(const Command CommandItem, const std::vector<std::pair<const int, colour_combiner>*> ExpectedOutput);
	void OnCurrentGroupsUpdate(const Command CommandItem, std::vector<std::pair<const int, colour_combiner>*>  CurrentGroups) {};
	void SpecificCommand(const Command command) {};
private:
    std::map<std::set<int>, int, cmpBySetSize> proxies;
	BinaryLightController* light;
	int threshhold = 0;
	int group_offset = 0;
};

