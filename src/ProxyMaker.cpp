#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Colour_Combiner.cpp"
#include <fstream>
#include <set>
#include "ProxyMaker.h"
#include <algorithm>
void ProxyMaker::print_proxies(std::map<std::set<int>, int, cmpBySetSize> proxies)
{
	for (auto proxy : proxies)
	{
		std::cout << proxy.second << ": ";
		for (auto key_part : proxy.first)
		{
			std::cout << key_part << ", ";
		}
		std::cout << '\n';
	}
}
std::map<std::set<int>, int, cmpBySetSize> ProxyMaker::proxy_filereader(std::string filename)
{
	std::string line;
	std::ifstream infile(filename);

	std::map<std::set<int>, int, cmpBySetSize> output;
	if (verbose)
	{
		std::cout << "Begin" << '\n';
	}

	if (infile.is_open())
	{
		while (std::getline(infile, line))
		{
			if (verbose)
			{
				std::cout << line << '\n';
			}
			std::istringstream iss = std::istringstream(line);

			std::string word;
			iss >> word;
			int converted_id = std::stoi(word);
			if (verbose)
			{
				std::cout << std::to_string(converted_id) + " Proxies: ";
			}

			std::set<int> input_ids;
			while (iss >> word)
			{
				input_ids.insert(std::stoi(word));
				if (verbose)
				{
					std::cout << word + ", ";
				}
			}
			if (verbose)
			{
				std::cout << '\n';
			}
			output[input_ids] = converted_id;
		}
	}
	return output;
}

//TODO MAKE OPTIONAL
Colour_Combiner ProxyMaker::get_from_data(int id, std::map<int, Colour_Combiner> input)
{
	for (auto entry : input)
	{
		if (id == entry.first)
		{
			return entry.second;
		}
	}
	return Colour_Combiner();
}
bool ProxyMaker::colours_equal(const Colour_Combiner c1, const Colour_Combiner c2)
{
	//There's an extremely rare chance two having different operations make the same result, so we don't
	//care about the command
	//if (c1.command != c2.command) { return false; }

	const auto Colour1 = c1.get_colour();
	const auto Colour2 = c2.get_colour();

	if (Colour1.red != Colour2.red | Colour1.blue != Colour2.blue | Colour1.green != Colour2.green)
	{
		return false;
	}

	return true;
}

std::map<int, Colour_Combiner> ProxyMaker::proxy_maker(std::map<int, Colour_Combiner> input, std::map<std::set<int>, int, cmpBySetSize> proxies)
{

	std::vector<int> Groups;

	for (auto item : input)
	{
		Groups.push_back(item.first);
	}

	std::map<int, Colour_Combiner> output;

	for (auto proxy : proxies)
	{
		bool found_all = proxy.first.size() > 0;

		if (verbose)
		{
			std::cout << "Beginning searches for: " << proxy.second << '\n';
		}
		for (auto group : proxy.first)
		{

			if (verbose)
			{
				std::cout << '\t' << "Searching for: " << std::to_string(group) << '\n';
			}
			if (std::find(Groups.begin(), Groups.end(), group) == Groups.end())
			{
				found_all = false;
				if (verbose)
				{
					std::cout << '\t' << "Didn't find it, terminating."
							  << "\n";
				}
				break;
			}
		}
		if (verbose)
		{
			std::cout << "Finished searches" << '\n'
					  << '\n';
		}

		if (found_all)
		{
			const int first_id = *(proxy.first.begin());
			if (verbose)
			{
				std::cout << '\n'
						  << "Proxy Detected for: " << std::to_string(proxy.second) << '\n';
			}

			auto new_setting = get_from_data(first_id, input);
			if (verbose)
			{
				std::cout << '\t' << "Ensuring all equal to: " << std::to_string(first_id) << '\n';
			}

			bool valid_proxy = true;
			for (auto entry : proxy.first)
			{
				if (colours_equal(new_setting, get_from_data(entry, input)) == false)
				{
					if (verbose)
					{
						std::cout << '\n'
								  << '\t' << "Proxy is not valid because groups are different colours" << '\n'
								  << '\n';
					}
					valid_proxy = false;
					break;
				}
			}
			if (valid_proxy == false)
			{
				break;
			}
			else if (verbose)
			{
				std::cout << '\n'
						  << '\t' << "Proxy verified for: " << std::to_string(first_id) << '\n';
			}

			int ID;

			for (auto groupID : proxy.first)
			{
				if (verbose)
				{
					std::cout << '\t' << '\t' << "Removing " << std::to_string(groupID) << '\n';
				}
				ID = groupID;
				Groups.erase(std::find(Groups.begin(), Groups.end(), groupID));
			}

			for (auto pair : input)
			{
				if (pair.first == ID)
				{
					if (verbose)
					{
						std::cout << '\t' << "Proxy group is: " << std::to_string(proxy.second) << " Using data from: " << std::to_string(ID) << '\n'
								  << '\n';
					}
					output[proxy.second] = pair.second;
					break;
				}
			}
		}
	}

	if (verbose)
	{
		std::cout << "Ensuring non-proxied groups are kept: " << '\n';
	}
	for (auto remaining : Groups)
	{
		if (verbose)
		{
			std::cout << '\t' << "Keeping: " << std::to_string(remaining) << '\n';
		};
		for (auto pair : input)
		{
			if (pair.first == remaining)
			{
				output[pair.first] = pair.second;
			}
		}
	}

	if (verbose)
	{
		std::cout << '\n';
	}

	return output;
}
