#ifndef Colour_Combiner_H
#define Colour_Combiner_H
#include "Colour.h"
#include "Command.h"
class Colour_Combiner
{
public:
	bool hue_changed() const
	{
		return ((colour_change.Hue != 0 && command != CommandOperation::set) |
				(command == CommandOperation::set && colour_change.Hue != currentColour.Hue));
	}

	bool sat_changed() const
	{
		return ((colour_change.Saturation != 0 && command != CommandOperation::set) |
				(command == CommandOperation::set && colour_change.Saturation != currentColour.Saturation));
	}
	bool brightness_changed() const
	{
		return ((colour_change.Brightness != 0 && command != CommandOperation::set) |
				(command == CommandOperation::set && colour_change.Brightness != currentColour.Brightness));
	}

	bool red_changed() const
	{
		return ((colour_change.red != 0 && command != CommandOperation::set) |
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

	Colour prev_colour() const
	{
		return currentColour;
	}

	Colour get_colour() const
	{
		Colour result = currentColour;
		switch (command)
		{
		case CommandOperation::set:
			return colour_change;
			break;
		case CommandOperation::add:
			result += colour_change;
			return result;
			break;
		case CommandOperation::Remove:
			result -= colour_change;
			return result;
			break;
		}
		return result;
	}

	void set_new(const Colour colour_change, const CommandOperation::CommandOperation cmd)
	{
		currentColour = get_colour();
		command = cmd;
		this->colour_change = colour_change;
	}

	Colour_Combiner() : currentColour("000000", true), colour_change("000000", true)
	{
	}

private:
	Colour currentColour;
	Colour colour_change;
	CommandOperation::CommandOperation command;
};

#endif