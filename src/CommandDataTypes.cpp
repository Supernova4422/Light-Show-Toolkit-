#ifndef LightShowCommands
#define LightShowCommands
#include <string>

enum CommandType
{
  ColourChange_RGB,
  ColourChange_HSV,
  Wait,
  Group,
  FunctionName,
  SpecificCommand
};

enum CommandOperation
{
  set,
  add,
  Remove
};

struct Command
{
  CommandType type;
  std::string value;
  CommandOperation Operation;
  int TimesToExecute;

  Command(CommandType type, std::string value, CommandOperation operation, int TimesToExecute) : type(type), value(value), Operation(operation), TimesToExecute(TimesToExecute) {}
};
#endif