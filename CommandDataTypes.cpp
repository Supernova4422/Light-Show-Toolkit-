#ifndef LightShowCommands
#define LightShowCommands
 
// Header code goes here
 

#include <string>

enum CommandType {ColourChange, Wait, Group, FunctionName, FunctionPointer};

enum CommandOperation { set, add, Remove };

struct Command {
  CommandType type;
  std::string value;
  CommandOperation Operation; 
  Command(){}
  Command(CommandType type, std::string value, CommandOperation operation) {
    this->type = type;
    this->value = value;
    this->Operation = operation;
  }
};

struct Function
{
  std::string Identifier;
  Command Commands[];

};

#endif