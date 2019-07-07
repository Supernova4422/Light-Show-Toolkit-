cmake_minimum_required(VERSION 3.7)

find_library(wiringPi_LIB wiringPi)
if (IS_DIRECTORY ${wiringPi_LIB})
	project(433)
	set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -std=c++17")
	set (CMAKE_BUILD_TYPE Debug)
	set (CMAKE_CXX_STANDARD 17)

	find_path(RC-Switch NAME RCSwitch.h HINTS "../rc-switch/")

	if(NOT IS_DIRECTORY ${RC-Switch})
		message("RC-Switch was not found. RC-Switch can be downloaded at: https://github.com/sui77/rc-switch however if you are not compiling to RPI this can be ignored")
	elseif(IS_DIRECTORY ${RC-Switch})

	message("Make sure to download wiringpi with the following commands:
	'git clone git://git.drogon.net/wiringPi',
	'cd wiringPi',
	'./build'")

		add_library(433 STATIC
			${RC-Switch}/RCSwitch.cpp
			BL_433.h
			BL_433.cpp
			)
		target_include_directories(433 PUBLIC ${RC-Switch})
		target_include_directories(433 PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
		target_include_directories(433 PUBLIC ../src)
		message("RC-Switch has been found, setting flag RPI")
		set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DRPI -lwiringPi -lwiringPiDev -lcrypt")

	endif(NOT IS_DIRECTORY ${RC-Switch})
elseif (NOT IS_DIRECTORY ${wiringPi_LIB})
	message("WiringPI has not been installed, therefore the 433 Transceiver will not be installed.")
endif(IS_DIRECTORY ${wiringPi_LIB})