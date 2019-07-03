#include "functional"
#include <string>
#include "SongPlayer.h"
class UserCommand
{
public:
	UserCommand(std::string input, std::string help,
				std::function<void(std::string)> func)
		: help(help), input(input), func(func)
	{
	}

	void run(std::string param)
	{
		func(param);
	}

	std::string get_help()
	{
		return input + ": " + help;
	}
	bool input_matches(std::string other_input)
	{
		return input == other_input;
	}

private:
	std::string help;
	std::string input;
	std::function<void(std::string)> func;
};