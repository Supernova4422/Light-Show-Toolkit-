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
    //Therefore it is the .LS format
    if ((FileToParse.back() == 's') | (FileToParse.back() == 'S')) {
        IntermediateFile = LSFormatReader.ProcessFile(FileToParse);
    }
    if ((FileToParse.back() == 'L') | (FileToParse.back() == 'l')) {
        std::cout << "Unfortunately, XML is not yet supported!" << std::endl;
    }
    if ((FileToParse.back() == 'N') | (FileToParse.back() == 'n')) {
        std::cout << "Unfortunately, JSON is not yet supported!" << std::endl;
    }
    
    if (IntermediateFile.empty()) {
        std::cout << "The file was empty!";
        return Factory.CreateFunctionHolder(IntermediateFile);
    } else {
        return Factory.CreateFunctionHolder(IntermediateFile);
    }
    
}
