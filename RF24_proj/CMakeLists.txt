cmake_minimum_required(VERSION 3.7)
project(RF24_proj)

find_path(RF24 NAME RF24.h)
add_library(RF24_proj
	RF24_Sender.cpp 
	RF24_Sender.h
	RF24_Factory.h
	RF24_Factory.cpp
	)
target_include_directories(RF24_proj PUBLIC ${RF24})
target_include_directories(RF24_proj PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_include_directories(RF24_proj PUBLIC ../src)
link_directories("/usr/local/lib/")
target_link_libraries(RF24_proj "rf24-bcm")

find_path(OpenMilight NAME MiLightRadio.h)

if(NOT IS_DIRECTORY ${V6_Encoding})
	message("V6_Encoding was not found. V6_Encoding can be downloaded at: https://github.com/sidoh/esp8266_milight_hub however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${V6_Encoding})
	message("V6_Encoding has been found")
	INCLUDE_DIRECTORIES(RF24_proj ${V6_Encoding}) 
	target_sources(RF24_proj PUBLIC ${V6_Encoding}/V2RFEncoding.h ${V6_Encoding}/V2RFEncoding.cpp)
endif(NOT IS_DIRECTORY ${V6_Encoding})

if(NOT IS_DIRECTORY ${OpenMilight})
	message("OpenMilight was not found. OpenMilight can be downloaded at: https://github.com/henryk/openmili however if you are not compiling to RPI this can be ignored")
elseif(IS_DIRECTORY ${OpenMilight})
	message("OpenMilight has been found")
	INCLUDE_DIRECTORIES(RF24_proj ${OpenMilight} ) 
	target_sources(RF24_proj PUBLIC ${OpenMilight}/PL1167_nRF24.cpp ${OpenMilight}/MiLightRadio.cpp ${OpenMilight}/MiLightRadio.h)
endif(NOT IS_DIRECTORY ${OpenMilight})






message("RF24 has been found, make sure to run the configuration file!")





