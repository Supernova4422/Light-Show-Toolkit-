#pragma once

#include "Command.h"
#include "ProgrammableLight.h"

class Fileout_Light : public ProgrammableLight
{
public:
	Fileout_Light(std::string label = std::string("DEFAULT_") + std::to_string(Fileout_Light::count), const size_t delay = 0) : delay(delay), label(label)
	{
		count += 1;
		std::cout << "All commands will print to console" << std::endl;
	};

	void RepostGroups(const std::map<int, Colour_Combiner> ExpectedOutput)
	{
		if (PostedNewGroups == false)
		{
			bool done_first = false;
			for (auto group : ExpectedOutput)
			{
				if (done_first == false)
				{
					done_first = true;
					std::cout << "=";
				}
				else
				{
					std::cout << "+";
				}
				std::cout << std::to_string(group.first) << std::endl;
			}

			PostedNewGroups = true;
		}
	}

	void EmitColour(const Command CommandItem,
					const std::map<int, Colour_Combiner> ExpectedOutput) override
	{

		RepostGroups(ExpectedOutput);

		Colour NewColour(CommandItem.value, CommandItem.type == ColourChange_RGB);

		switch (CommandItem.Operation)
		{
		case set:
			std::cout << "=";
			break;
		case add:
			std::cout << "+";
			break;
		case Remove:
			std::cout << "-";
			break;
		}

		std::cout
			<< std::to_string(NewColour.red)
			<< std::to_string(NewColour.green)
			<< std::to_string(NewColour.blue)
			<< std::endl;

		if (delay > 0)
		{
			std::cout << std::to_string(delay) << std::endl;
		}

		std::cout << std::endl;
	}

	void SpecificCommand(const Command command,
						 const std::map<int, Colour_Combiner> CurrentGroups) override
	{
		RepostGroups(CurrentGroups);
		std::cout << command.value << std::endl;
	};

	void OnCurrentGroupsUpdate(const Command CommandItem,
							   const std::map<int, Colour_Combiner> CurrentGroups) override
	{
		PostedNewGroups = false;
	};

	void OnStart() override{};
	void OnEnd() override{};

private:
	bool PostedNewGroups = false;
	size_t delay;
	std::string label;
	static int count;
};
