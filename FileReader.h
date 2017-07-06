#include <string>
#include <vector> 
#include <utility> 
#include <map>

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

class FileReader
{
  public:  
    virtual std::map<std::string, std::vector<std::string>> ProcessFile(const std::string& FilePath);
    
};

class LightShowFileReader: public FileReader
{
  public:
  std::map<std::string, std::vector<std::string>>  ProcessFile(const std::string& FilePath);
  private:
    std::vector<std::string> SplitLineIntoCommands(const std::string& Line);
    std::vector<std::string> CleanUpCommands(const std::vector<std::string>& StringVector);
};



