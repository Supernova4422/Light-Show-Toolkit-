#pragma once
#include <map>
#include <vector>
#include <string>
#include <iostream>
#include <sstream>
#include "Color_Combiner.cpp"
#include <fstream>
#include <set>
#include <cstddef>
#include <cstdio>

struct cmpBySetSize {
	bool operator()(const std::set<int>& a, const std::set<int>& b) const {
		if (a.size() == b.size()) {
			for (int item : a) { //See if each element of the set is the same
				if (b.find(item) == b.end()) {
					return true;
				}
			}
			return false;
		}
		return a.size() > b.size();
	}
};

struct ProxyMaker {
	static const bool verbose = true;

	static void print_proxies(std::map<std::set<int>, int, cmpBySetSize> proxies);
	
	static std::map<std::set<int>, int, cmpBySetSize> proxy_filereader(std::string filename);
	
	//TODO MAKE OPTIONAL
	static colour_combiner get_from_data (int id, std::vector<std::pair<const int, colour_combiner>*> input);
	static bool colors_equal (colour_combiner c1, colour_combiner c2);
	static std::vector<std::pair<const int, colour_combiner>*> proxy_maker(
		std::vector<std::pair<const int, colour_combiner>*> input, 
		std::map<std::set<int>, int, cmpBySetSize> proxies);

};
