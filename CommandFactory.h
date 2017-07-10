#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
using namespace std;

class CommandFactory {
    public:
        Command ParseCommand(string CommandInput);
        std::map<std::string, std::vector<Command>> CreateFunctionHolder (std::map<std::string, std::vector<std::string>> IntermediateFile);
        std::map<std::string, std::vector<pair<CommandType, std::string>>> ProcessDictionary (std::map<std::string, std::vector<std::string>> ParsedData);
        void ConvertMacrosToPointers (std::map<std::string, std::vector<Command>> *FunctionCollection);
    private: 
        vector<string> RemoveTrailingWhiteSpace(const vector<string>& StringVector);
        void PrintAll(std::map <string, vector<string>> FunctionsWithCommands );
};
