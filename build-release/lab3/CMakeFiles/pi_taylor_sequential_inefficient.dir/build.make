# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:

#=============================================================================
# Special targets provided by cmake.

# Disable implicit rules so canonical targets will work.
.SUFFIXES:

# Disable VCS-based implicit rules.
% : %,v

# Disable VCS-based implicit rules.
% : RCS/%

# Disable VCS-based implicit rules.
% : RCS/%,v

# Disable VCS-based implicit rules.
% : SCCS/s.%

# Disable VCS-based implicit rules.
% : s.%

.SUFFIXES: .hpux_make_needs_suffix_list

# Command-line flag to silence nested $(MAKE).
$(VERBOSE)MAKESILENT = -s

#Suppress display of executed commands.
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
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/jorge/mrgcv/pacs

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/jorge/mrgcv/pacs/build-release

# Include any dependencies generated for this target.
include lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/compiler_depend.make

# Include the progress variables for this target.
include lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/progress.make

# Include the compile flags for this target's objects.
include lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/flags.make

lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o: lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/flags.make
lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o: ../lab3/pi_taylor_sequential_inefficient.cc
lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o: lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/jorge/mrgcv/pacs/build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o"
	cd /home/jorge/mrgcv/pacs/build-release/lab3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o -MF CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o.d -o CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o -c /home/jorge/mrgcv/pacs/lab3/pi_taylor_sequential_inefficient.cc

lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.i"
	cd /home/jorge/mrgcv/pacs/build-release/lab3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/jorge/mrgcv/pacs/lab3/pi_taylor_sequential_inefficient.cc > CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.i

lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.s"
	cd /home/jorge/mrgcv/pacs/build-release/lab3 && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/jorge/mrgcv/pacs/lab3/pi_taylor_sequential_inefficient.cc -o CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.s

# Object files for target pi_taylor_sequential_inefficient
pi_taylor_sequential_inefficient_OBJECTS = \
"CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o"

# External object files for target pi_taylor_sequential_inefficient
pi_taylor_sequential_inefficient_EXTERNAL_OBJECTS =

lab3/pi_taylor_sequential_inefficient: lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/pi_taylor_sequential_inefficient.cc.o
lab3/pi_taylor_sequential_inefficient: lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/build.make
lab3/pi_taylor_sequential_inefficient: lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/jorge/mrgcv/pacs/build-release/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable pi_taylor_sequential_inefficient"
	cd /home/jorge/mrgcv/pacs/build-release/lab3 && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/pi_taylor_sequential_inefficient.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/build: lab3/pi_taylor_sequential_inefficient
.PHONY : lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/build

lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/clean:
	cd /home/jorge/mrgcv/pacs/build-release/lab3 && $(CMAKE_COMMAND) -P CMakeFiles/pi_taylor_sequential_inefficient.dir/cmake_clean.cmake
.PHONY : lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/clean

lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/depend:
	cd /home/jorge/mrgcv/pacs/build-release && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/jorge/mrgcv/pacs /home/jorge/mrgcv/pacs/lab3 /home/jorge/mrgcv/pacs/build-release /home/jorge/mrgcv/pacs/build-release/lab3 /home/jorge/mrgcv/pacs/build-release/lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : lab3/CMakeFiles/pi_taylor_sequential_inefficient.dir/depend

