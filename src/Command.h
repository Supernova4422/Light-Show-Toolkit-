#pragma once
#include "CommandType.h"
#include "CommandOperation.h"
#include <string>
struct Command
{
  CommandType type;
  std::string value;
  CommandOperation Operation;
  unsigned int TimesToExecute;

  Command(CommandType type, std::string value, CommandOperation operation, unsigned int TimesToExecute) : type(type), value(value), Operation(operation), TimesToExecute(TimesToExecute) {}
};