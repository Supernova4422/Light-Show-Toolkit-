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

  Command(const std::string CommandInput) : TimesToExecute(1), Operation(CommandOperation::set), type(CommandType::FunctionName), value(CommandInput)
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
      value = "";
      for (char c : value)
      {
        if (ParsedAmountOfTimesToExecute)
        {
          value += c;
        }
        else if (isalpha(c))
        {
          TimesToExecute = std::stoi(value);
          value = c;
          ParsedAmountOfTimesToExecute = true;
        }
        else
        {
          value += c;
        }
      }
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