# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.10

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build

# Include any dependencies generated for this target.
include test/CMakeFiles/dim_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/dim_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/dim_test.dir/flags.make

test/CMakeFiles/dim_test.dir/dim_test.cc.o: test/CMakeFiles/dim_test.dir/flags.make
test/CMakeFiles/dim_test.dir/dim_test.cc.o: ../test/dim_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/dim_test.dir/dim_test.cc.o"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/dim_test.dir/dim_test.cc.o -c /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/dim_test.cc

test/CMakeFiles/dim_test.dir/dim_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/dim_test.dir/dim_test.cc.i"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/dim_test.cc > CMakeFiles/dim_test.dir/dim_test.cc.i

test/CMakeFiles/dim_test.dir/dim_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/dim_test.dir/dim_test.cc.s"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/dim_test.cc -o CMakeFiles/dim_test.dir/dim_test.cc.s

test/CMakeFiles/dim_test.dir/dim_test.cc.o.requires:

.PHONY : test/CMakeFiles/dim_test.dir/dim_test.cc.o.requires

test/CMakeFiles/dim_test.dir/dim_test.cc.o.provides: test/CMakeFiles/dim_test.dir/dim_test.cc.o.requires
	$(MAKE) -f test/CMakeFiles/dim_test.dir/build.make test/CMakeFiles/dim_test.dir/dim_test.cc.o.provides.build
.PHONY : test/CMakeFiles/dim_test.dir/dim_test.cc.o.provides

test/CMakeFiles/dim_test.dir/dim_test.cc.o.provides.build: test/CMakeFiles/dim_test.dir/dim_test.cc.o


# Object files for target dim_test
dim_test_OBJECTS = \
"CMakeFiles/dim_test.dir/dim_test.cc.o"

# External object files for target dim_test
dim_test_EXTERNAL_OBJECTS =

test/dim_test: test/CMakeFiles/dim_test.dir/dim_test.cc.o
test/dim_test: test/CMakeFiles/dim_test.dir/build.make
test/dim_test: lemon/libemon.a
test/dim_test: test/CMakeFiles/dim_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable dim_test"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/dim_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/dim_test.dir/build: test/dim_test

.PHONY : test/CMakeFiles/dim_test.dir/build

test/CMakeFiles/dim_test.dir/requires: test/CMakeFiles/dim_test.dir/dim_test.cc.o.requires

.PHONY : test/CMakeFiles/dim_test.dir/requires

test/CMakeFiles/dim_test.dir/clean:
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && $(CMAKE_COMMAND) -P CMakeFiles/dim_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/dim_test.dir/clean

test/CMakeFiles/dim_test.dir/depend:
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1 /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test/CMakeFiles/dim_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/dim_test.dir/depend

