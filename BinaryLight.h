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
	BinaryLight(int upperlimit , BinaryLightController* light) : threshhold(threshhold) , light(light) {
		std::cout << "All commands will print to console, focusing on turning off and on" << std::endl;
		std::cout << "Upper limit set to: " << upperlimit << std::endl;

		std::cout << "FileController" << std::endl;
		light->initialise();
	};

	void SetColourForCurrentGroups(const Colour OutputColour) {};
	void EmitColour(const Command CommandItem, const std::vector<std::pair<const int, Colour>*> ExpectedOutput);
	void OnCurrentGroupsUpdate(const Command CommandItem, std::vector<std::pair<const int, Colour>*>  CurrentGroups) {};
	void SpecificCommand(const Command command) {};
private: 
	BinaryLightController* light;
	int threshhold;
	bool PostedNewGroups = false;
};

