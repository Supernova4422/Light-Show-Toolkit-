#pragma once
#include "BinaryLightController.h"

class BinLight_SYSFS : public BinaryLightController
{
public:
	BinLight_SYSFS(std::string directory = "/sys/class/gpio/", std::string exp_append = "/export", std::string val_append = "/value", std::string dir_append = "/direction")
		: directory(directory), exp_append(exp_append), val_append(val_append), dir_append(dir_append) {};

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

