#pragma once
#include "ProgrammableLight.h"
#include <iomanip>
#include <string>
#include <fstream>
#include <cstdlib>
#include <errno.h>
#include "BinaryLightController.h"

class BinaryLight : public ProgrammableLight
{
public:
	BinaryLight(BinaryLightController* light, int upperlimit = 1,  int group_offset = 0) : threshhold(threshhold) , light(light), group_offset(group_offset) {
		std::cout << std::endl << "Binary Light loaded" << std::endl;
		std::cout << "All commands will print to console, focusing on turning off and on" << std::endl;
		std::cout << "Upper limit set to: " << upperlimit << std::endl;

		
		light->initialise();
	};

	void SetColourForCurrentGroups(const Colour OutputColour) {};
	void EmitColour(const Command CommandItem, const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
	void OnCurrentGroupsUpdate(const Command CommandItem, std::vector<std::pair<const int, Colour>*>  CurrentGroups) {};
	void SpecificCommand(const Command command) {};
private: 
	BinaryLightController* light;
	int threshhold = 0;
	int group_offset = 0;
	bool PostedNewGroups = false;
};

