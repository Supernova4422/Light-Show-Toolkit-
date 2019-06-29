#include "CommandDataTypes.cpp"
#include <map>
#include "Colour.h"
#include "LIGHT_COMMAND_TYPE.h"
#include "Color_Combiner.cpp"

struct Light_Command
{
	Command command;
	std::map<int, colour_combiner> groups;
	LIGHT_COMMAND_TYPE light_command;

	Light_Command(const Command command,
				  const std::map<int, colour_combiner> groups,
				  const LIGHT_COMMAND_TYPE light_command)
		: command(command), groups(groups), light_command(light_command) {}
};