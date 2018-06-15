#pragma once
#include <fstream>
class BinaryLightController
{
public:
	virtual void initialise() = 0;
	virtual void turnon(int group) = 0;
	virtual void turnoff(int group) = 0;
};

