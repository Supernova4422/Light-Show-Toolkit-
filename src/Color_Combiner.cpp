#ifndef COLOUR_COMBINER
#define COLOUR_COMBINER
#include "Colour.h"
#include "CommandDataTypes.cpp"
class colour_combiner
{
public:
	CommandOperation command;
	bool hue_changed() const {
		return ( (colour_change.Hue != 0 && command != CommandOperation::set) |
			(command == CommandOperation::set && colour_change.Hue != currentColour.Hue));
	}

	bool sat_changed() const {
		return ( (colour_change.Saturation != 0 && command != CommandOperation::set) |
			(command == CommandOperation::set && colour_change.Saturation != currentColour.Saturation));
	}
	bool brightness_changed() const {
		return ( (colour_change.Brightness != 0 && command != CommandOperation::set) |
			(command == CommandOperation::set && colour_change.Brightness != currentColour.Brightness));
	}

	bool red_changed() const {
		return ( (colour_change.red != 0 && command != CommandOperation::set ) |
			(command == CommandOperation::set && colour_change.red != currentColour.red));
	}

	bool green_changed() const
	{
		return ((colour_change.green != 0 && command != CommandOperation::set) |
			(command == CommandOperation::set && colour_change.green != currentColour.green));
	}

	bool blue_changed() const
	{
		return ((colour_change.blue != 0 && command != CommandOperation::set) |
			(command == CommandOperation::set && colour_change.blue != currentColour.blue));
	}

	Colour prev_colour() const {
		return currentColour;
	}

	Colour get_colour() const {
		Colour result = currentColour;
		switch (command) {
		case set:
			return colour_change;
			break;
		case add:
			result += colour_change;
			return result;
			break;
		case Remove:
			result -= colour_change;
			return result;
			break;
		}
	}

	void set_new(const Colour colour_change, const CommandOperation cmd) {
		currentColour = get_colour();
		command = cmd;
		this->colour_change = colour_change;
	}

private:
	Colour currentColour;
	Colour colour_change;
};

#endif