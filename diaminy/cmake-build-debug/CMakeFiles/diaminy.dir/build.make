# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.13

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe"

# The command to remove a file.
RM = "C:\Program Files\JetBrains\CLion 2018.3.4\bin\cmake\win\bin\cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/diaminy.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/diaminy.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/diaminy.dir/flags.make

CMakeFiles/diaminy.dir/main.cpp.obj: CMakeFiles/diaminy.dir/flags.make
CMakeFiles/diaminy.dir/main.cpp.obj: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/diaminy.dir/main.cpp.obj"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles\diaminy.dir\main.cpp.obj -c "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\main.cpp"

CMakeFiles/diaminy.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/diaminy.dir/main.cpp.i"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\main.cpp" > CMakeFiles\diaminy.dir\main.cpp.i

CMakeFiles/diaminy.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/diaminy.dir/main.cpp.s"
	C:\PROGRA~2\MINGW-~1\I686-8~1.0-P\mingw32\bin\G__~1.EXE $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\main.cpp" -o CMakeFiles\diaminy.dir\main.cpp.s

# Object files for target diaminy
diaminy_OBJECTS = \
"CMakeFiles/diaminy.dir/main.cpp.obj"

# External object files for target diaminy
diaminy_EXTERNAL_OBJECTS =

diaminy.exe: CMakeFiles/diaminy.dir/main.cpp.obj
diaminy.exe: CMakeFiles/diaminy.dir/build.make
diaminy.exe: CMakeFiles/diaminy.dir/linklibs.rsp
diaminy.exe: CMakeFiles/diaminy.dir/objects1.rsp
diaminy.exe: CMakeFiles/diaminy.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug\CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable diaminy.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\diaminy.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/diaminy.dir/build: diaminy.exe

.PHONY : CMakeFiles/diaminy.dir/build

CMakeFiles/diaminy.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles\diaminy.dir\cmake_clean.cmake
.PHONY : CMakeFiles/diaminy.dir/clean

CMakeFiles/diaminy.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy" "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy" "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug" "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug" "C:\Users\Pawel Maczuga PC\Documents\algorytmy\diaminy\cmake-build-debug\CMakeFiles\diaminy.dir\DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/diaminy.dir/depend

