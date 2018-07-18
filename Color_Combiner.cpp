#include "Colour.h"
#include "CommandDataTypes.cpp"
class colour_combiner
{
public:
	CommandOperation command;
	bool hue_changed() {
		if (colour_change.Hue != 0 |
			(command == CommandOperation::set && next_colour.Hue != currentColour.Hue));
	}

	bool sat_changed() { 
		if (colour_change.Saturation != 0 |
			(command == CommandOperation::set && next_colour.Saturation != currentColour.Saturation));
	}
	bool brightness_changed() { 
		if (colour_change.Brightness != 0 |
			(command == CommandOperation::set && next_colour.Brightness != currentColour.Brightness)); 
	}

	bool red_changed() {
		if (colour_change.red != 0 |
			(command == CommandOperation::set && next_colour.red != currentColour.red));
	}
	bool green_changed() {
		if (colour_change.green != 0 |
			(command == CommandOperation::set && next_colour.green != currentColour.green));
	}
	bool blue_changed() {
		if (colour_change.blue != 0 |
			(command == CommandOperation::set && colour_change.blue != currentColour.blue));
	}

	Colour get_colour() {
		switch (command) {
		case set:
			return colour_change;
			break;
		case add:
			Colour result = currentColour;
			result += colour_change;
			return result;
			break;
		case Remove:
			Colour result = currentColour;
			result -= colour_change;
			break;
		}
	}

	void set_new(Colour colour_change, CommandOperation cmd) {
		currentColour = get_colour();
		command = cmd;
		this->colour_change = colour_change;
	}
private: 
	Colour currentColour;
	Colour colour_change;
};