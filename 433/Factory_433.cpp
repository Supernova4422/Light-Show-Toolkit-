#include "BL_433.h"
#include "Factory_433.h"
#include "BinaryLight.h"
ProgrammableLight* Factory_433::get_light() {
	return new BinaryLight(new BL_433(), 16, 0);
}
