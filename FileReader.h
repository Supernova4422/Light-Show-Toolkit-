#ifndef FILE_READER
#define FILE_READER

#include <string>
#include <vector> 
#include <utility> 
#include <map>
#include "CommandDataTypes.cpp"
class FileReader
{
  public:  
    virtual std::map<std::string, std::vector<std::string>> ProcessFile(const std::string& FilePath);
    
};



#endif