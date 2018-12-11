
#include "BL_433.h"
#include <fstream>
#include <string>
#include <iostream>
#include <sstream>


BL_433::BL_433()
{
    
    std::cout << std::endl << "Loading the 433mhz Codes" << std::endl;
    std::ifstream myfile("BL_433_Codes.txt");

    int read_value = 0x00;
    std::cout << "Begin Reading" << std::endl;
    while (myfile >> read_value)
    {
        std::cout << std::dec << read_value << std::endl;
        int val = 0;
        myfile >> val;
        std::cout << val << std::endl;
        on_cmds[read_value] = val;
        myfile >> val;
        std::cout << val << std::endl;
        off_cmds[read_value] = val;
    }
    std::cout << "Finished Reading" << std::endl;

    if (wiringPiSetup() != -1) {
        mySwitch.enableTransmit(0);
        std::cout << "Initialised WiringPi, 433 Transmitter as well" << std::endl;
    }
    std::string line;
    int repeats = 3;
    int pulselength = 350; 
    std::ifstream infile("bl433_settings.txt");
    if (infile.is_open()) {
        std::getline(infile, line);
        repeats = std::stoi(line);
        std::getline(infile, line);
        pulselength = std::stoi(line);
        std::cout << "Configuring transmitter based on file: " << '\n';
        std::cout << '\t' << "Repeats: " << repeats << '\n';
        std::cout << '\t' << "PulseLength: " << pulselength << '\n';
    } else {
        std::cout << "Error finding file for configuring transmitter" << '\n';
        
    }
	mySwitch.disableReceive();
	mySwitch.setRepeatTransmit(repeats);
	mySwitch.setPulseLength(pulselength);

}

void BL_433::initialise()
{
	std::cout << "Please ensure that you have run this program using sudo" << std::endl;
	std::cout << "433mhz sender is ready" << std::endl;

}

void BL_433::turnon(int group)
{
    std::cout << on_cmds[group] << std::endl;
    if ( on_cmds[group] != 0) {
		mySwitch.send(on_cmds[group] , 24);
	}
}


void BL_433::turnoff(int group)
{
    std::cout << off_cmds[group] << std::endl;
	if ( off_cmds[group] != 0) {
		mySwitch.send(off_cmds[group] , 24);
	}
    
}
