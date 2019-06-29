#include "LIGHT_COMMAND_TYPE.h"
#include "Light_Command.h"
#include <queue>
#include <optional>

class Light_Command_Queue
{
public:
	void push(const Command command, const std::map<int, colour_combiner> CurrentGroups, LIGHT_COMMAND_TYPE)
	{
		auto cmd = Light_Command(
			command,
			CurrentGroups,
			LIGHT_COMMAND_TYPE::SPECIFIC_COMMAND);

		std::lock_guard<std::mutex> lock(mut);
		queue.push(cmd);
	}

	std::optional<Light_Command> pop()
	{

		std::lock_guard<std::mutex> lock(mut);
		if (queue.size() > 0)
		{
			auto item = queue.front();
			queue.pop();
			return std::optional<Light_Command>(item);
		}
		else
		{
			return std::nullopt;
		}
	}

	void clear()
	{
		std::lock_guard<std::mutex> lock(mut);
		queue = std::queue<Light_Command>();
	}

private:
	std::queue<Light_Command> queue;
	std::mutex mut;
};