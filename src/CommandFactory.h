#ifndef CommandFactoryDef
#define CommandFactoryDef

#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
using namespace std;

class CommandFactory
{
public:
    std::map<std::string, std::vector<Command>> CreateFunctionHolder(std::map<std::string, std::vector<std::string>> IntermediateFile) const;
    Command ParseCommand(std::string CommandInput) const;

private:
    vector<string> CleanupCommands(const vector<string> &StringVector) const;
    string RemoveTrailingWhiteSpace(const string &StringToFix) const;
    bool IsWhiteSpace(char c) const;
    void PrintAll(std::map<string, vector<string>> FunctionsWithCommands);
};
#endif