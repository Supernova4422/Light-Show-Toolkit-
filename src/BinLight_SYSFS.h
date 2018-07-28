#pragma once
#include "BinaryLightController.h"
#include <fstream>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <iostream>
class BinLight_SYSFS : public BinaryLightController
{
public:
	BinLight_SYSFS();

	~BinLight_SYSFS();
	void initialise();
	void turnon(int group);
	void turnoff(int group);
private: 
	bool pin_initialised[40];
	void exportPin(int group);
	std::string directory = "/sys/class/gpio/";
	std::string exp_append = "/export";
	std::string val_append = "/value";
	std::string dir_append = "/direction";
};

