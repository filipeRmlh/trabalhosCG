# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.12

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
CMAKE_COMMAND = /home/filipe/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.3911.40/bin/cmake/linux/bin/cmake

# The command to remove a file.
RM = /home/filipe/.local/share/JetBrains/Toolbox/apps/CLion/ch-0/182.3911.40/bin/cmake/linux/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/Trabalho2_CG2018.2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Trabalho2_CG2018.2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Trabalho2_CG2018.2.dir/flags.make

CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o: CMakeFiles/Trabalho2_CG2018.2.dir/flags.make
CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o -c "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/main.cpp"

CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/main.cpp" > CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.i

CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/main.cpp" -o CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.s

# Object files for target Trabalho2_CG2018.2
Trabalho2_CG2018_2_OBJECTS = \
"CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o"

# External object files for target Trabalho2_CG2018.2
Trabalho2_CG2018_2_EXTERNAL_OBJECTS =

Trabalho2_CG2018.2: CMakeFiles/Trabalho2_CG2018.2.dir/main.cpp.o
Trabalho2_CG2018.2: CMakeFiles/Trabalho2_CG2018.2.dir/build.make
Trabalho2_CG2018.2: /usr/lib/x86_64-linux-gnu/libGL.so
Trabalho2_CG2018.2: /usr/lib/x86_64-linux-gnu/libGLU.so
Trabalho2_CG2018.2: /usr/lib/x86_64-linux-gnu/libglut.so
Trabalho2_CG2018.2: CMakeFiles/Trabalho2_CG2018.2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Trabalho2_CG2018.2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Trabalho2_CG2018.2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Trabalho2_CG2018.2.dir/build: Trabalho2_CG2018.2

.PHONY : CMakeFiles/Trabalho2_CG2018.2.dir/build

CMakeFiles/Trabalho2_CG2018.2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Trabalho2_CG2018.2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Trabalho2_CG2018.2.dir/clean

CMakeFiles/Trabalho2_CG2018.2.dir/depend:
	cd "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2" "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2" "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug" "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug" "/home/filipe/CLionProjects/Trabalho 2 - CG 2018.2/cmake-build-debug/CMakeFiles/Trabalho2_CG2018.2.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/Trabalho2_CG2018.2.dir/depend
