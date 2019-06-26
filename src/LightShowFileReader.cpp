// in myclass.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <cctype>
#include "LightShowFileReader.h"
using namespace std;

std::map<std::string, std::vector<std::string>>  LightShowFileReader::ProcessFile(const string& FilePath) {
   ifstream myfile (FilePath);
   bool ReadingForFunction = true;

   string CurrentLine;
   vector<string> Commands;

   string CurrentWord;

   string CurrentFunctionName;
   vector<string> CurrentCommandList;
   bool NewLine = false;
   const char ForwardSlash = '/';
   char PreviousChar = 0;

   std::map <string, vector<string>> FunctionsWithCommands;
   if (myfile.is_open()) {
       while (getline(myfile,CurrentLine)) {
            NewLine = true;
            bool ReadingLine = true;
            for (char CurrentChar : CurrentLine) {
				if (CurrentChar == '\r')
				{
					//In Linux new lines will be read as this, to ensure consistency, we just skip them all
				} else {
					if (ReadingLine)
					{
						// Move the /* and // Removal to here
						if (CurrentChar == ForwardSlash && PreviousChar == ForwardSlash ) {
							ReadingLine = false;
							CurrentWord = CurrentWord.substr(0,CurrentWord.size() - 1);
						} else if (CurrentChar == '{' && (ReadingForFunction == true) ) {
							CurrentFunctionName = CurrentWord;
							CurrentWord = "";

							ReadingForFunction = false;
						} else if (CurrentChar == '}' && (ReadingForFunction == false)) {
							CurrentCommandList.push_back(CurrentWord);
							//TODO THROW ERROR IF FUNCTIONNAME STARTS WITH NUMBER
							FunctionsWithCommands.insert(std::pair<string,vector<string>>(CurrentFunctionName , CurrentCommandList));
							//Lets see if we can change this to be the object that's edited later

							CurrentCommandList.clear();
							CurrentWord = "";
							CurrentFunctionName = "";
							ReadingForFunction = true;
						} else if ((CurrentChar == ':') && (ReadingForFunction == false))  {
							CurrentCommandList.push_back(CurrentWord);
							CurrentWord = "";
						} else if (NewLine && (ReadingForFunction == false) ) {

							if (CurrentWord == "") {
								CurrentWord += CurrentChar;
							} else {
								CurrentCommandList.push_back(CurrentWord);
								CurrentWord = "";
								CurrentWord += CurrentChar;
							}
						}
						else {
							CurrentWord += CurrentChar;
						}

						PreviousChar = CurrentChar;
					}
				NewLine = false;
				}
			}
        }
   }
   return FunctionsWithCommands;
}

vector<string> LightShowFileReader::SplitLineIntoCommands(const string& Line)
{
    vector<string> CommandsOnLine;

    string Command;
    const char Delimeter = ':';

    bool ReadingLine = true;
    string CommentsOnLine; //We may use this later, lets keep it

    for(const char c : Line) {
        if (ReadingLine)
        {
            if (c == Delimeter) {
                CommandsOnLine.push_back(Command);
                Command = "";
            } else {
                Command = Command + c;
            }
        }
    }

    CommandsOnLine.push_back(Command);
    return CommandsOnLine;
}

vector<string> LightShowFileReader::CleanUpCommands(const vector<string>& StringVector) {
    //vector<string> CleanedCommands = RemoveTrailingWhiteSpace(StringVector);
    return StringVector;
}
