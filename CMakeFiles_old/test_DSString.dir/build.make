# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.23

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
CMAKE_COMMAND = /usr/local/es7/bin/cmake

# The command to remove a file.
RM = /usr/local/es7/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan

# Include any dependencies generated for this target.
include CMakeFiles/test_DSString.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/test_DSString.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/test_DSString.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/test_DSString.dir/flags.make

CMakeFiles/test_DSString.dir/test_DSString.cpp.o: CMakeFiles/test_DSString.dir/flags.make
CMakeFiles/test_DSString.dir/test_DSString.cpp.o: test_DSString.cpp
CMakeFiles/test_DSString.dir/test_DSString.cpp.o: CMakeFiles/test_DSString.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/test_DSString.dir/test_DSString.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_DSString.dir/test_DSString.cpp.o -MF CMakeFiles/test_DSString.dir/test_DSString.cpp.o.d -o CMakeFiles/test_DSString.dir/test_DSString.cpp.o -c /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/test_DSString.cpp

CMakeFiles/test_DSString.dir/test_DSString.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_DSString.dir/test_DSString.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/test_DSString.cpp > CMakeFiles/test_DSString.dir/test_DSString.cpp.i

CMakeFiles/test_DSString.dir/test_DSString.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_DSString.dir/test_DSString.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/test_DSString.cpp -o CMakeFiles/test_DSString.dir/test_DSString.cpp.s

CMakeFiles/test_DSString.dir/DSString.cpp.o: CMakeFiles/test_DSString.dir/flags.make
CMakeFiles/test_DSString.dir/DSString.cpp.o: DSString.cpp
CMakeFiles/test_DSString.dir/DSString.cpp.o: CMakeFiles/test_DSString.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/test_DSString.dir/DSString.cpp.o"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT CMakeFiles/test_DSString.dir/DSString.cpp.o -MF CMakeFiles/test_DSString.dir/DSString.cpp.o.d -o CMakeFiles/test_DSString.dir/DSString.cpp.o -c /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/DSString.cpp

CMakeFiles/test_DSString.dir/DSString.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/test_DSString.dir/DSString.cpp.i"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/DSString.cpp > CMakeFiles/test_DSString.dir/DSString.cpp.i

CMakeFiles/test_DSString.dir/DSString.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/test_DSString.dir/DSString.cpp.s"
	/usr/bin/g++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/DSString.cpp -o CMakeFiles/test_DSString.dir/DSString.cpp.s

# Object files for target test_DSString
test_DSString_OBJECTS = \
"CMakeFiles/test_DSString.dir/test_DSString.cpp.o" \
"CMakeFiles/test_DSString.dir/DSString.cpp.o"

# External object files for target test_DSString
test_DSString_EXTERNAL_OBJECTS =

test_DSString: CMakeFiles/test_DSString.dir/test_DSString.cpp.o
test_DSString: CMakeFiles/test_DSString.dir/DSString.cpp.o
test_DSString: CMakeFiles/test_DSString.dir/build.make
test_DSString: CMakeFiles/test_DSString.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable test_DSString"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/test_DSString.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/test_DSString.dir/build: test_DSString
.PHONY : CMakeFiles/test_DSString.dir/build

CMakeFiles/test_DSString.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/test_DSString.dir/cmake_clean.cmake
.PHONY : CMakeFiles/test_DSString.dir/clean

CMakeFiles/test_DSString.dir/depend:
	cd /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan /users7/cse/ltirjan/assignment-2-don-t-be-sentimental-otirjan/CMakeFiles/test_DSString.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/test_DSString.dir/depend

