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
include test/CMakeFiles/adaptors_test.dir/depend.make

# Include the progress variables for this target.
include test/CMakeFiles/adaptors_test.dir/progress.make

# Include the compile flags for this target's objects.
include test/CMakeFiles/adaptors_test.dir/flags.make

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o: test/CMakeFiles/adaptors_test.dir/flags.make
test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o: ../test/adaptors_test.cc
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/adaptors_test.dir/adaptors_test.cc.o -c /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/adaptors_test.cc

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/adaptors_test.dir/adaptors_test.cc.i"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/adaptors_test.cc > CMakeFiles/adaptors_test.dir/adaptors_test.cc.i

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/adaptors_test.dir/adaptors_test.cc.s"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test/adaptors_test.cc -o CMakeFiles/adaptors_test.dir/adaptors_test.cc.s

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.requires:

.PHONY : test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.requires

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.provides: test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.requires
	$(MAKE) -f test/CMakeFiles/adaptors_test.dir/build.make test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.provides.build
.PHONY : test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.provides

test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.provides.build: test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o


# Object files for target adaptors_test
adaptors_test_OBJECTS = \
"CMakeFiles/adaptors_test.dir/adaptors_test.cc.o"

# External object files for target adaptors_test
adaptors_test_EXTERNAL_OBJECTS =

test/adaptors_test: test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o
test/adaptors_test: test/CMakeFiles/adaptors_test.dir/build.make
test/adaptors_test: lemon/libemon.a
test/adaptors_test: test/CMakeFiles/adaptors_test.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable adaptors_test"
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/adaptors_test.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
test/CMakeFiles/adaptors_test.dir/build: test/adaptors_test

.PHONY : test/CMakeFiles/adaptors_test.dir/build

test/CMakeFiles/adaptors_test.dir/requires: test/CMakeFiles/adaptors_test.dir/adaptors_test.cc.o.requires

.PHONY : test/CMakeFiles/adaptors_test.dir/requires

test/CMakeFiles/adaptors_test.dir/clean:
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test && $(CMAKE_COMMAND) -P CMakeFiles/adaptors_test.dir/cmake_clean.cmake
.PHONY : test/CMakeFiles/adaptors_test.dir/clean

test/CMakeFiles/adaptors_test.dir/depend:
	cd /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1 /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/test /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test /home/giacomo/CLionProjects/inconsistency/dependencies/lemon-1.3.1/build/test/CMakeFiles/adaptors_test.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : test/CMakeFiles/adaptors_test.dir/depend

