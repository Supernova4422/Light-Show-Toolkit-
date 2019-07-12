#include "BinLight_SYSFS.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>

BinLight_SYSFS::BinLight_SYSFS()
{
	std::cout << std::endl
			  << "Loading the file_editor binary light" << std::endl;
	std::ifstream myfile("config/FILEOUT_CONFIG.txt.txt");
	if (myfile.is_open())
	{
		std::cout << "Opened config for BinLight, loading the directory, export_append, val_append and dir_append" << std::endl;
		getline(myfile, directory);
		getline(myfile, exp_append);
		getline(myfile, val_append);
		getline(myfile, dir_append);
		myfile.close();
		std::cout << "Finished loading the configuration" << std::endl
				  << std::endl;
	}
}

void BinLight_SYSFS::initialise()
{
	std::cout << "Please ensure that you have run this program using sudo" << std::endl;
	std::cout << "Also this program will not unexport pins" << std::endl;
}

void BinLight_SYSFS::turnon(int group)
{
	std::string setval_filepath = directory + "gpio" + std::to_string(group) + val_append;
	std::ofstream setval_file;
	setval_file.open(setval_filepath.c_str());
	setval_file << 1;
	setval_file.close();
}

void BinLight_SYSFS::turnoff(int group)
{
	std::string setval_filepath = directory + "gpio" + std::to_string(group) + val_append;
	std::ofstream setval_file;
	setval_file.open(setval_filepath.c_str());
	setval_file << 0;
	setval_file.close();
}
//heavily based on http://www.hertaville.com/introduction-to-accessing-the-raspberry-pis-gpio-in-c.html
void BinLight_SYSFS::exportPin(int group)
{
	if (pin_initialised[group] == false)
	{
		//Export the pins
		std::string exportPin_filepath = directory + "gpio" + exp_append;
		std::ofstream exportgpio_file(exportPin_filepath.c_str());
		if (exportgpio_file.bad())
		{
			std::cout << " OPERATION FAILED: Unable to export GPIO" << group << " ." << std::endl;
		}
		exportgpio_file << group;
		exportgpio_file.close();
		//Set their direction
		std::string setdir_filepath = directory + "gpio" + std::to_string(group) + dir_append;
		std::ofstream setDir_file(setdir_filepath.c_str());
		setDir_file << "out";
		setDir_file << "out";
		setDir_file.close();
		pin_initialised[group] = true;
	}
}