# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.14

# Delete rule output on recipe failure.
.DELETE_ON_ERROR:


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
CMAKE_COMMAND = /snap/clion/73/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /snap/clion/73/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/pawel/Documents/algorytmy/diaminy

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/pawel/Documents/algorytmy/diaminy/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/diaminy1.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/diaminy1.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/diaminy1.dir/flags.make

CMakeFiles/diaminy1.dir/graph.cpp.o: CMakeFiles/diaminy1.dir/flags.make
CMakeFiles/diaminy1.dir/graph.cpp.o: ../graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/pawel/Documents/algorytmy/diaminy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/diaminy1.dir/graph.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/diaminy1.dir/graph.cpp.o -c /home/pawel/Documents/algorytmy/diaminy/graph.cpp

CMakeFiles/diaminy1.dir/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diaminy1.dir/graph.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/pawel/Documents/algorytmy/diaminy/graph.cpp > CMakeFiles/diaminy1.dir/graph.cpp.i

CMakeFiles/diaminy1.dir/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diaminy1.dir/graph.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/pawel/Documents/algorytmy/diaminy/graph.cpp -o CMakeFiles/diaminy1.dir/graph.cpp.s

# Object files for target diaminy1
diaminy1_OBJECTS = \
"CMakeFiles/diaminy1.dir/graph.cpp.o"

# External object files for target diaminy1
diaminy1_EXTERNAL_OBJECTS =

diaminy1: CMakeFiles/diaminy1.dir/graph.cpp.o
diaminy1: CMakeFiles/diaminy1.dir/build.make
diaminy1: CMakeFiles/diaminy1.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/pawel/Documents/algorytmy/diaminy/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable diaminy1"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/diaminy1.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/diaminy1.dir/build: diaminy1

.PHONY : CMakeFiles/diaminy1.dir/build

CMakeFiles/diaminy1.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/diaminy1.dir/cmake_clean.cmake
.PHONY : CMakeFiles/diaminy1.dir/clean

CMakeFiles/diaminy1.dir/depend:
	cd /home/pawel/Documents/algorytmy/diaminy/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/pawel/Documents/algorytmy/diaminy /home/pawel/Documents/algorytmy/diaminy /home/pawel/Documents/algorytmy/diaminy/cmake-build-debug /home/pawel/Documents/algorytmy/diaminy/cmake-build-debug /home/pawel/Documents/algorytmy/diaminy/cmake-build-debug/CMakeFiles/diaminy1.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/diaminy1.dir/depend

