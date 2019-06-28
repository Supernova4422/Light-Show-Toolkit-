#pragma once
#include "BinaryLightController.h"
class GPIO_PI : public BinaryLightController
{
public:
	void initialise();
	void turnon(int group);
	void turnoff(int group);
};
