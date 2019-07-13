#pragma once
#include "CommandType.h"
#include "CommandOperation.h"
#include <string>
struct Command
{
  CommandType::CommandType type;
  std::string value;
  CommandOperation::CommandOperation Operation;
  unsigned int TimesToExecute;

  Command(CommandType::CommandType type, std::string value, CommandOperation::CommandOperation operation, unsigned int TimesToExecute) : type(type), value(value), Operation(operation), TimesToExecute(TimesToExecute) {}

  Command(const std::string CommandInput) : type(CommandType::FunctionName), value(CommandInput), Operation(CommandOperation::set), TimesToExecute(1)
  {
    std::string GroupIdentifier = "Group";

    if (value[0] == '+')
    {
      Operation = CommandOperation::add;
      value = value.erase(0, 1);
    }
    else if (value[0] == '-')
    {
      Operation = CommandOperation::Remove;
      value = value.erase(0, 1);
    }
    else if (value[0] == '=')
    {
      Operation = CommandOperation::set;
      value = value.erase(0, 1);
    }

    if ((value[0] == '[') && (value.back() == ']'))
    {
      value = value.erase(0, 1);
      value = value.substr(0, value.size() - 1);
      type = CommandType::SpecificCommand;
    }
    else if (value[0] == '#')
    {
      value = value.erase(0, 1);
      type = CommandType::ColourChange_RGB;
    }
    else if (value[0] == '$')
    {
      value = value.erase(0, 1);
      type = CommandType::ColourChange_HSV;
    }
    else if (value.compare(0, GroupIdentifier.size(), GroupIdentifier) == 0)
    {
      value = value.erase(0, GroupIdentifier.size());
      type = CommandType::Group;
    }
    else if (isdigit(value[0]))
    {
      bool ParsedAmountOfTimesToExecute = false;
      std::string temp_value = "";
      for (auto c : value)
      {
        if (ParsedAmountOfTimesToExecute)
        {
          temp_value += c;
        }
        else if (isalpha(c))
        {
          TimesToExecute = std::stoi(temp_value);
          ParsedAmountOfTimesToExecute = true;
          temp_value = c;
        }
        else
        {
          temp_value += c;
        }
      }

      value = temp_value;

      if (ParsedAmountOfTimesToExecute)
      {
        type = CommandType::FunctionName;
      }
      else
      {
        type = CommandType::Wait;
      }
    }
  }
};