#ifndef LightShowCommands
#define LightShowCommands
 
// Header code goes here
 

#include <string>

enum CommandType {ColourChange, Wait, Group, FunctionName, SpecificCommand};

enum CommandOperation { set, add, Remove };

struct Command {
  CommandType type;
  std::string value;
  CommandOperation Operation;
  int TimesToExecute = 1; 
  Command(){}
  Command(CommandType type, std::string value, CommandOperation operation, int TimesToExecute) {
    this->type = type;
    this->value = value;
    this->Operation = operation;
    this->TimesToExecute = TimesToExecute;
  }
};



#endif