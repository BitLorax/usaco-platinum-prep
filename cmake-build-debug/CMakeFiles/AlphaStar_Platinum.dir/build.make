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
CMAKE_COMMAND = "/cygdrive/c/Users/Will Liang/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe"

# The command to remove a file.
RM = "/cygdrive/c/Users/Will Liang/.CLion2018.2/system/cygwin_cmake/bin/cmake.exe" -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum"

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug"

# Include any dependencies generated for this target.
include CMakeFiles/AlphaStar_Platinum.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/AlphaStar_Platinum.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/AlphaStar_Platinum.dir/flags.make

CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o: CMakeFiles/AlphaStar_Platinum.dir/flags.make
CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o: ../src/day12_FinalExam/P2_BarnExpansion.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir="/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o"
	/usr/bin/c++.exe  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o -c "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/src/day12_FinalExam/P2_BarnExpansion.cpp"

CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.i"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/src/day12_FinalExam/P2_BarnExpansion.cpp" > CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.i

CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.s"
	/usr/bin/c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/src/day12_FinalExam/P2_BarnExpansion.cpp" -o CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.s

# Object files for target AlphaStar_Platinum
AlphaStar_Platinum_OBJECTS = \
"CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o"

# External object files for target AlphaStar_Platinum
AlphaStar_Platinum_EXTERNAL_OBJECTS =

AlphaStar_Platinum.exe: CMakeFiles/AlphaStar_Platinum.dir/src/day12_FinalExam/P2_BarnExpansion.cpp.o
AlphaStar_Platinum.exe: CMakeFiles/AlphaStar_Platinum.dir/build.make
AlphaStar_Platinum.exe: CMakeFiles/AlphaStar_Platinum.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir="/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug/CMakeFiles" --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable AlphaStar_Platinum.exe"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/AlphaStar_Platinum.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/AlphaStar_Platinum.dir/build: AlphaStar_Platinum.exe

.PHONY : CMakeFiles/AlphaStar_Platinum.dir/build

CMakeFiles/AlphaStar_Platinum.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/AlphaStar_Platinum.dir/cmake_clean.cmake
.PHONY : CMakeFiles/AlphaStar_Platinum.dir/clean

CMakeFiles/AlphaStar_Platinum.dir/depend:
	cd "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug" && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum" "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum" "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug" "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug" "/cygdrive/c/Users/Will Liang/Dropbox/CS/AlphaStar Platinum/cmake-build-debug/CMakeFiles/AlphaStar_Platinum.dir/DependInfo.cmake" --color=$(COLOR)
.PHONY : CMakeFiles/AlphaStar_Platinum.dir/depend
