#include <string>
#include <vector>
#include <utility>
#include <map>
#include <iostream>
#include "FileParserHandler.h"
#include "CommandDataTypes.cpp"

std::map<std::string, std::vector<Command>> FileParserHandler::ParseFile (std::string FileToParse) {
    std::cout << "Parsing: " << FileToParse <<std::endl;
    std::map<std::string, std::vector<std::string>> IntermediateFile;
    IntermediateFile = LSFormatReader.ProcessFile(FileToParse);

    if (IntermediateFile.empty()) {
        std::cout << "The file was empty!" << std::endl;
    }
    
    return Factory.CreateFunctionHolder(IntermediateFile);
    
}
