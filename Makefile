# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.7

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:


# Remove some rules from gmake that .SUFFIXES does not remove.
SUFFIXES =

.SUFFIXES: .hpux_make_needs_suffix_list


# Suppress display of executed commands.
$(VERBOSE).SILENT:


# A target that is always out of date.
cmake_force:

.PHONY : cmake_force

#=============================================================================
# Set environment variables for the build.

# The shell in which to execute make rules.
SHELL = /bin/sh

# The CMake executable.
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pi/Light-Show-Toolkit-

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pi/Light-Show-Toolkit-

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/bin/cmake-gui -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/pi/Light-Show-Toolkit-/CMakeFiles /home/pi/Light-Show-Toolkit-/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/pi/Light-Show-Toolkit-/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named LightShowProject

# Build rule for target.
LightShowProject: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 LightShowProject
.PHONY : LightShowProject

# fast build rule for target.
LightShowProject/fast:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/build
.PHONY : LightShowProject/fast

BinLight_SYSFS.o: BinLight_SYSFS.cpp.o

.PHONY : BinLight_SYSFS.o

# target to build an object file
BinLight_SYSFS.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinLight_SYSFS.cpp.o
.PHONY : BinLight_SYSFS.cpp.o

BinLight_SYSFS.i: BinLight_SYSFS.cpp.i

.PHONY : BinLight_SYSFS.i

# target to preprocess a source file
BinLight_SYSFS.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinLight_SYSFS.cpp.i
.PHONY : BinLight_SYSFS.cpp.i

BinLight_SYSFS.s: BinLight_SYSFS.cpp.s

.PHONY : BinLight_SYSFS.s

# target to generate assembly for a file
BinLight_SYSFS.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinLight_SYSFS.cpp.s
.PHONY : BinLight_SYSFS.cpp.s

BinaryLight.o: BinaryLight.cpp.o

.PHONY : BinaryLight.o

# target to build an object file
BinaryLight.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinaryLight.cpp.o
.PHONY : BinaryLight.cpp.o

BinaryLight.i: BinaryLight.cpp.i

.PHONY : BinaryLight.i

# target to preprocess a source file
BinaryLight.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinaryLight.cpp.i
.PHONY : BinaryLight.cpp.i

BinaryLight.s: BinaryLight.cpp.s

.PHONY : BinaryLight.s

# target to generate assembly for a file
BinaryLight.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/BinaryLight.cpp.s
.PHONY : BinaryLight.cpp.s

Colour.o: Colour.cpp.o

.PHONY : Colour.o

# target to build an object file
Colour.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Colour.cpp.o
.PHONY : Colour.cpp.o

Colour.i: Colour.cpp.i

.PHONY : Colour.i

# target to preprocess a source file
Colour.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Colour.cpp.i
.PHONY : Colour.cpp.i

Colour.s: Colour.cpp.s

.PHONY : Colour.s

# target to generate assembly for a file
Colour.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Colour.cpp.s
.PHONY : Colour.cpp.s

CommandDataTypes.o: CommandDataTypes.cpp.o

.PHONY : CommandDataTypes.o

# target to build an object file
CommandDataTypes.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandDataTypes.cpp.o
.PHONY : CommandDataTypes.cpp.o

CommandDataTypes.i: CommandDataTypes.cpp.i

.PHONY : CommandDataTypes.i

# target to preprocess a source file
CommandDataTypes.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandDataTypes.cpp.i
.PHONY : CommandDataTypes.cpp.i

CommandDataTypes.s: CommandDataTypes.cpp.s

.PHONY : CommandDataTypes.s

# target to generate assembly for a file
CommandDataTypes.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandDataTypes.cpp.s
.PHONY : CommandDataTypes.cpp.s

CommandFactory.o: CommandFactory.cpp.o

.PHONY : CommandFactory.o

# target to build an object file
CommandFactory.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandFactory.cpp.o
.PHONY : CommandFactory.cpp.o

CommandFactory.i: CommandFactory.cpp.i

.PHONY : CommandFactory.i

# target to preprocess a source file
CommandFactory.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandFactory.cpp.i
.PHONY : CommandFactory.cpp.i

CommandFactory.s: CommandFactory.cpp.s

.PHONY : CommandFactory.s

# target to generate assembly for a file
CommandFactory.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandFactory.cpp.s
.PHONY : CommandFactory.cpp.s

CommandLineInterface.o: CommandLineInterface.cpp.o

.PHONY : CommandLineInterface.o

# target to build an object file
CommandLineInterface.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandLineInterface.cpp.o
.PHONY : CommandLineInterface.cpp.o

CommandLineInterface.i: CommandLineInterface.cpp.i

.PHONY : CommandLineInterface.i

# target to preprocess a source file
CommandLineInterface.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandLineInterface.cpp.i
.PHONY : CommandLineInterface.cpp.i

CommandLineInterface.s: CommandLineInterface.cpp.s

.PHONY : CommandLineInterface.s

# target to generate assembly for a file
CommandLineInterface.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/CommandLineInterface.cpp.s
.PHONY : CommandLineInterface.cpp.s

ConsoleLight.o: ConsoleLight.cpp.o

.PHONY : ConsoleLight.o

# target to build an object file
ConsoleLight.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/ConsoleLight.cpp.o
.PHONY : ConsoleLight.cpp.o

ConsoleLight.i: ConsoleLight.cpp.i

.PHONY : ConsoleLight.i

# target to preprocess a source file
ConsoleLight.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/ConsoleLight.cpp.i
.PHONY : ConsoleLight.cpp.i

ConsoleLight.s: ConsoleLight.cpp.s

.PHONY : ConsoleLight.s

# target to generate assembly for a file
ConsoleLight.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/ConsoleLight.cpp.s
.PHONY : ConsoleLight.cpp.s

FileParserHandler.o: FileParserHandler.cpp.o

.PHONY : FileParserHandler.o

# target to build an object file
FileParserHandler.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/FileParserHandler.cpp.o
.PHONY : FileParserHandler.cpp.o

FileParserHandler.i: FileParserHandler.cpp.i

.PHONY : FileParserHandler.i

# target to preprocess a source file
FileParserHandler.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/FileParserHandler.cpp.i
.PHONY : FileParserHandler.cpp.i

FileParserHandler.s: FileParserHandler.cpp.s

.PHONY : FileParserHandler.s

# target to generate assembly for a file
FileParserHandler.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/FileParserHandler.cpp.s
.PHONY : FileParserHandler.cpp.s

GPIO_PI.o: GPIO_PI.cpp.o

.PHONY : GPIO_PI.o

# target to build an object file
GPIO_PI.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GPIO_PI.cpp.o
.PHONY : GPIO_PI.cpp.o

GPIO_PI.i: GPIO_PI.cpp.i

.PHONY : GPIO_PI.i

# target to preprocess a source file
GPIO_PI.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GPIO_PI.cpp.i
.PHONY : GPIO_PI.cpp.i

GPIO_PI.s: GPIO_PI.cpp.s

.PHONY : GPIO_PI.s

# target to generate assembly for a file
GPIO_PI.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GPIO_PI.cpp.s
.PHONY : GPIO_PI.cpp.s

GroupManager.o: GroupManager.cpp.o

.PHONY : GroupManager.o

# target to build an object file
GroupManager.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GroupManager.cpp.o
.PHONY : GroupManager.cpp.o

GroupManager.i: GroupManager.cpp.i

.PHONY : GroupManager.i

# target to preprocess a source file
GroupManager.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GroupManager.cpp.i
.PHONY : GroupManager.cpp.i

GroupManager.s: GroupManager.cpp.s

.PHONY : GroupManager.s

# target to generate assembly for a file
GroupManager.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/GroupManager.cpp.s
.PHONY : GroupManager.cpp.s

LightShowFileReader.o: LightShowFileReader.cpp.o

.PHONY : LightShowFileReader.o

# target to build an object file
LightShowFileReader.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/LightShowFileReader.cpp.o
.PHONY : LightShowFileReader.cpp.o

LightShowFileReader.i: LightShowFileReader.cpp.i

.PHONY : LightShowFileReader.i

# target to preprocess a source file
LightShowFileReader.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/LightShowFileReader.cpp.i
.PHONY : LightShowFileReader.cpp.i

LightShowFileReader.s: LightShowFileReader.cpp.s

.PHONY : LightShowFileReader.s

# target to generate assembly for a file
LightShowFileReader.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/LightShowFileReader.cpp.s
.PHONY : LightShowFileReader.cpp.s

Milight.o: Milight.cpp.o

.PHONY : Milight.o

# target to build an object file
Milight.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Milight.cpp.o
.PHONY : Milight.cpp.o

Milight.i: Milight.cpp.i

.PHONY : Milight.i

# target to preprocess a source file
Milight.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Milight.cpp.i
.PHONY : Milight.cpp.i

Milight.s: Milight.cpp.s

.PHONY : Milight.s

# target to generate assembly for a file
Milight.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/Milight.cpp.s
.PHONY : Milight.cpp.s

SDL_TCPSender.o: SDL_TCPSender.cpp.o

.PHONY : SDL_TCPSender.o

# target to build an object file
SDL_TCPSender.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_TCPSender.cpp.o
.PHONY : SDL_TCPSender.cpp.o

SDL_TCPSender.i: SDL_TCPSender.cpp.i

.PHONY : SDL_TCPSender.i

# target to preprocess a source file
SDL_TCPSender.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_TCPSender.cpp.i
.PHONY : SDL_TCPSender.cpp.i

SDL_TCPSender.s: SDL_TCPSender.cpp.s

.PHONY : SDL_TCPSender.s

# target to generate assembly for a file
SDL_TCPSender.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_TCPSender.cpp.s
.PHONY : SDL_TCPSender.cpp.s

SDL_UDPSender.o: SDL_UDPSender.cpp.o

.PHONY : SDL_UDPSender.o

# target to build an object file
SDL_UDPSender.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_UDPSender.cpp.o
.PHONY : SDL_UDPSender.cpp.o

SDL_UDPSender.i: SDL_UDPSender.cpp.i

.PHONY : SDL_UDPSender.i

# target to preprocess a source file
SDL_UDPSender.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_UDPSender.cpp.i
.PHONY : SDL_UDPSender.cpp.i

SDL_UDPSender.s: SDL_UDPSender.cpp.s

.PHONY : SDL_UDPSender.s

# target to generate assembly for a file
SDL_UDPSender.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SDL_UDPSender.cpp.s
.PHONY : SDL_UDPSender.cpp.s

SongPlayer.o: SongPlayer.cpp.o

.PHONY : SongPlayer.o

# target to build an object file
SongPlayer.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SongPlayer.cpp.o
.PHONY : SongPlayer.cpp.o

SongPlayer.i: SongPlayer.cpp.i

.PHONY : SongPlayer.i

# target to preprocess a source file
SongPlayer.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SongPlayer.cpp.i
.PHONY : SongPlayer.cpp.i

SongPlayer.s: SongPlayer.cpp.s

.PHONY : SongPlayer.s

# target to generate assembly for a file
SongPlayer.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/SongPlayer.cpp.s
.PHONY : SongPlayer.cpp.s

main.o: main.cpp.o

.PHONY : main.o

# target to build an object file
main.cpp.o:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/main.cpp.o
.PHONY : main.cpp.o

main.i: main.cpp.i

.PHONY : main.i

# target to preprocess a source file
main.cpp.i:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/main.cpp.i
.PHONY : main.cpp.i

main.s: main.cpp.s

.PHONY : main.s

# target to generate assembly for a file
main.cpp.s:
	$(MAKE) -f CMakeFiles/LightShowProject.dir/build.make CMakeFiles/LightShowProject.dir/main.cpp.s
.PHONY : main.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... LightShowProject"
	@echo "... BinLight_SYSFS.o"
	@echo "... BinLight_SYSFS.i"
	@echo "... BinLight_SYSFS.s"
	@echo "... BinaryLight.o"
	@echo "... BinaryLight.i"
	@echo "... BinaryLight.s"
	@echo "... Colour.o"
	@echo "... Colour.i"
	@echo "... Colour.s"
	@echo "... CommandDataTypes.o"
	@echo "... CommandDataTypes.i"
	@echo "... CommandDataTypes.s"
	@echo "... CommandFactory.o"
	@echo "... CommandFactory.i"
	@echo "... CommandFactory.s"
	@echo "... CommandLineInterface.o"
	@echo "... CommandLineInterface.i"
	@echo "... CommandLineInterface.s"
	@echo "... ConsoleLight.o"
	@echo "... ConsoleLight.i"
	@echo "... ConsoleLight.s"
	@echo "... FileParserHandler.o"
	@echo "... FileParserHandler.i"
	@echo "... FileParserHandler.s"
	@echo "... GPIO_PI.o"
	@echo "... GPIO_PI.i"
	@echo "... GPIO_PI.s"
	@echo "... GroupManager.o"
	@echo "... GroupManager.i"
	@echo "... GroupManager.s"
	@echo "... LightShowFileReader.o"
	@echo "... LightShowFileReader.i"
	@echo "... LightShowFileReader.s"
	@echo "... Milight.o"
	@echo "... Milight.i"
	@echo "... Milight.s"
	@echo "... SDL_TCPSender.o"
	@echo "... SDL_TCPSender.i"
	@echo "... SDL_TCPSender.s"
	@echo "... SDL_UDPSender.o"
	@echo "... SDL_UDPSender.i"
	@echo "... SDL_UDPSender.s"
	@echo "... SongPlayer.o"
	@echo "... SongPlayer.i"
	@echo "... SongPlayer.s"
	@echo "... main.o"
	@echo "... main.i"
	@echo "... main.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

