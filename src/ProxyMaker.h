#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Colour_Combiner.cpp"
#include <fstream>
#include <set>
#include <cstddef>
#include <cstdio>

struct cmpBySetSize
{
	bool operator()(const std::set<int> &a, const std::set<int> &b) const
	{
		if (a.size() == b.size())
		{
			for (int item : a)
			{ //See if each element of the set is the same
				if (b.find(item) == b.end())
				{
					return true;
				}
			}
			return false;
		}
		return a.size() > b.size();
	}
};

struct ProxyMaker
{
	static const bool verbose = false;

	static void print_proxies(std::map<std::set<int>, int, cmpBySetSize> proxies);

	static std::map<std::set<int>, int, cmpBySetSize> proxy_filereader(std::string filename);

	//TODO MAKE OPTIONAL
<<<<<<< HEAD
	static Colour_Combiner get_from_data(int id, std::vector<std::pair<const int, Colour_Combiner> *> input);

	static bool colours_equal(Colour_Combiner c1, Colour_Combiner c2);

	static std::vector<std::pair<const int, Colour_Combiner> *> proxy_maker(
		std::vector<std::pair<const int, Colour_Combiner> *> input,
=======
	static Colour_Combiner get_from_data(int id, std::map<int, Colour_Combiner> input);
	static bool colours_equal(Colour_Combiner c1, Colour_Combiner c2);
	static std::map<int, Colour_Combiner> proxy_maker(
		std::map<int, Colour_Combiner> input,
>>>>>>> 033ce288d9292d359845386dab6b2a99638b6832
		std::map<std::set<int>, int, cmpBySetSize> proxies);
};
