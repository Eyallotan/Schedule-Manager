# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.15

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
CMAKE_COMMAND = /usr/local/bin/cmake

# The command to remove a file.
RM = /usr/local/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug

# Include any dependencies generated for this target.
include CMakeFiles/Wet2.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/Wet2.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/Wet2.dir/flags.make

CMakeFiles/Wet2.dir/main.cpp.o: CMakeFiles/Wet2.dir/flags.make
CMakeFiles/Wet2.dir/main.cpp.o: ../main.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/Wet2.dir/main.cpp.o"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/Wet2.dir/main.cpp.o -c /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/main.cpp

CMakeFiles/Wet2.dir/main.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/Wet2.dir/main.cpp.i"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/main.cpp > CMakeFiles/Wet2.dir/main.cpp.i

CMakeFiles/Wet2.dir/main.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/Wet2.dir/main.cpp.s"
	/usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/main.cpp -o CMakeFiles/Wet2.dir/main.cpp.s

# Object files for target Wet2
Wet2_OBJECTS = \
"CMakeFiles/Wet2.dir/main.cpp.o"

# External object files for target Wet2
Wet2_EXTERNAL_OBJECTS =

Wet2: CMakeFiles/Wet2.dir/main.cpp.o
Wet2: CMakeFiles/Wet2.dir/build.make
Wet2: CMakeFiles/Wet2.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable Wet2"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/Wet2.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/Wet2.dir/build: Wet2

.PHONY : CMakeFiles/Wet2.dir/build

CMakeFiles/Wet2.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/Wet2.dir/cmake_clean.cmake
.PHONY : CMakeFiles/Wet2.dir/clean

CMakeFiles/Wet2.dir/depend:
	cd /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug /mnt/c/Data/Technion/SemesterC/DataSt/HW/HW4/Git/cmake-build-debug/CMakeFiles/Wet2.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/Wet2.dir/depend

