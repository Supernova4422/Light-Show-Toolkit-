#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
using namespace std;

class CommandFactory {
    public:
        Command ParseCommand(string CommandInput);
        std::map<std::string, std::vector<pair<CommandType, std::string>>> ProcessDictionary (std::map<std::string, std::vector<std::string>> ParsedData);
    private: 
        vector<string> RemoveTrailingWhiteSpace(const vector<string>& StringVector);
};
