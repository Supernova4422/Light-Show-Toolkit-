#include <RF24_Sender.h>
#include "RF24_Factory.h"
ProgrammableLight* RF24_Factory::get_light() {
	return new RF24_Sender(MILIGHT_VERSION::V5);
}
