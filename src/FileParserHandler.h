#include <string>
#include <vector>
#include <utility>
#include <map>
#include "CommandDataTypes.cpp"
#include "LightShowFileReader.h"
#include "CommandFactory.h"
class FileParserHandler
{
    public:
        std::map<std::string, std::vector<Command>> ParseFile (std::string FileToParse);
    private: 
        LightShowFileReader LSFormatReader;
        CommandFactory Factory; 
};
