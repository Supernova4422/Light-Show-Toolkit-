cmake_minimum_required(VERSION 3.7)
project(433)
find_path(RC-Switch NAME RCSwitch.h)
if(NOT IS_DIRECTORY ${RC-Switch})
	message("RC-Switch was not found. RC-Switch can be downloaded at: https://github.com/sui77/rc-switch however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${RC-Switch})
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
