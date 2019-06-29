// in myclass.cpp
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <utility>
#include <cctype>
#include "LightShowFileReader.h"

std::map<std::string, std::vector<std::string>> LightShowFileReader::ProcessFile(const std::string &FilePath)
{
	std::ifstream myfile(FilePath);
	bool outsideFunction = true;

	std::string CurrentLine;
	std::vector<std::string> Commands;

	std::string CurrentWord;

	std::string CurrentFunctionName;
	std::vector<std::string> CurrentCommandList;
	bool NewLine = false;
	const char ForwardSlash = '/';
	char PreviousChar = 0;

	std::map<std::string, std::vector<std::string>> FunctionsWithCommands;
	if (myfile.is_open())
	{
		while (getline(myfile, CurrentLine))
		{
			NewLine = true;
			for (char CurrentChar : CurrentLine)
			{
				if (CurrentChar == '\r')
				{
					continue;
				}

				if (CurrentChar == ForwardSlash && PreviousChar == ForwardSlash)
				{
					CurrentWord = CurrentWord.substr(0, CurrentWord.size() - 1);
					break;
				}
				else if (CurrentChar == '{' && (outsideFunction == true))
				{
					CurrentFunctionName = CurrentWord;
					if (CurrentFunctionName[0] < 'a' || CurrentFunctionName[0] > 'Z')
					{
						//throw "Invalid File";
					}
					CurrentWord = "";
					outsideFunction = false;
				}
				else if (CurrentChar == '}' && (outsideFunction == false))
				{
					CurrentCommandList.push_back(CurrentWord);
					FunctionsWithCommands.insert(std::pair<std::string, std::vector<std::string>>(CurrentFunctionName, CurrentCommandList));
					//Lets see if we can change this to be the object that's edited later
					CurrentCommandList.clear();
					CurrentWord = "";
					CurrentFunctionName = "";
					outsideFunction = true;
				}
				else if ((CurrentChar == ':' | CurrentChar == ' ') && (outsideFunction == false) && (CurrentWord != ""))
				{
					CurrentCommandList.push_back(CurrentWord);
					CurrentWord = "";
				}
				else
				{
					CurrentWord += CurrentChar;
				}

				PreviousChar = CurrentChar;
				NewLine = false;
			}
			if (CurrentWord != "")
			{
				CurrentCommandList.push_back(CurrentWord);
				CurrentWord = "";
			}
		}
	}
	return FunctionsWithCommands;
}

std::vector<std::string> LightShowFileReader::CleanUpCommands(const std::vector<std::string> &stringvector)
{
	//std::vector<std::string> CleanedCommands = RemoveTrailingWhiteSpace(std::stringstd::vector);
	return stringvector;
}
