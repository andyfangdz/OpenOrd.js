# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.1/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.1/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/andy/Downloads/OpenOrd

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/andy/Downloads/OpenOrd/build

# Include any dependencies generated for this target.
include CMakeFiles/OpenOrd.js.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/OpenOrd.js.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/OpenOrd.js.dir/flags.make

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o: CMakeFiles/OpenOrd.js.dir/flags.make
CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o: CMakeFiles/OpenOrd.js.dir/includes_CXX.rsp
CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o: ../src/DensityGrid.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andy/Downloads/OpenOrd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o -c /Users/andy/Downloads/OpenOrd/src/DensityGrid.cpp

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.i"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andy/Downloads/OpenOrd/src/DensityGrid.cpp > CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.i

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.s"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andy/Downloads/OpenOrd/src/DensityGrid.cpp -o CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.s

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.requires:

.PHONY : CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.requires

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.provides: CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenOrd.js.dir/build.make CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.provides.build
.PHONY : CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.provides

CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.provides.build: CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o


CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o: CMakeFiles/OpenOrd.js.dir/flags.make
CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o: CMakeFiles/OpenOrd.js.dir/includes_CXX.rsp
CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o: ../src/graph.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andy/Downloads/OpenOrd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o -c /Users/andy/Downloads/OpenOrd/src/graph.cpp

CMakeFiles/OpenOrd.js.dir/src/graph.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenOrd.js.dir/src/graph.cpp.i"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andy/Downloads/OpenOrd/src/graph.cpp > CMakeFiles/OpenOrd.js.dir/src/graph.cpp.i

CMakeFiles/OpenOrd.js.dir/src/graph.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenOrd.js.dir/src/graph.cpp.s"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andy/Downloads/OpenOrd/src/graph.cpp -o CMakeFiles/OpenOrd.js.dir/src/graph.cpp.s

CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.requires:

.PHONY : CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.requires

CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.provides: CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenOrd.js.dir/build.make CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.provides.build
.PHONY : CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.provides

CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.provides.build: CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o


CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o: CMakeFiles/OpenOrd.js.dir/flags.make
CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o: CMakeFiles/OpenOrd.js.dir/includes_CXX.rsp
CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o: ../src/parse.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/Users/andy/Downloads/OpenOrd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Building CXX object CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o -c /Users/andy/Downloads/OpenOrd/src/parse.cpp

CMakeFiles/OpenOrd.js.dir/src/parse.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/OpenOrd.js.dir/src/parse.cpp.i"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /Users/andy/Downloads/OpenOrd/src/parse.cpp > CMakeFiles/OpenOrd.js.dir/src/parse.cpp.i

CMakeFiles/OpenOrd.js.dir/src/parse.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/OpenOrd.js.dir/src/parse.cpp.s"
	/Users/andy/Downloads/emsdk_portable/emscripten/1.35.0/em++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /Users/andy/Downloads/OpenOrd/src/parse.cpp -o CMakeFiles/OpenOrd.js.dir/src/parse.cpp.s

CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.requires:

.PHONY : CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.requires

CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.provides: CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.requires
	$(MAKE) -f CMakeFiles/OpenOrd.js.dir/build.make CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.provides.build
.PHONY : CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.provides

CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.provides.build: CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o


# Object files for target OpenOrd.js
OpenOrd_js_OBJECTS = \
"CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o" \
"CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o" \
"CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o"

# External object files for target OpenOrd.js
OpenOrd_js_EXTERNAL_OBJECTS =

OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o
OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o
OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o
OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/build.make
OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/objects1.rsp
OpenOrd.js.js: CMakeFiles/OpenOrd.js.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/Users/andy/Downloads/OpenOrd/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_4) "Linking CXX executable OpenOrd.js.js"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/OpenOrd.js.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/OpenOrd.js.dir/build: OpenOrd.js.js

.PHONY : CMakeFiles/OpenOrd.js.dir/build

CMakeFiles/OpenOrd.js.dir/requires: CMakeFiles/OpenOrd.js.dir/src/DensityGrid.cpp.o.requires
CMakeFiles/OpenOrd.js.dir/requires: CMakeFiles/OpenOrd.js.dir/src/graph.cpp.o.requires
CMakeFiles/OpenOrd.js.dir/requires: CMakeFiles/OpenOrd.js.dir/src/parse.cpp.o.requires

.PHONY : CMakeFiles/OpenOrd.js.dir/requires

CMakeFiles/OpenOrd.js.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/OpenOrd.js.dir/cmake_clean.cmake
.PHONY : CMakeFiles/OpenOrd.js.dir/clean

CMakeFiles/OpenOrd.js.dir/depend:
	cd /Users/andy/Downloads/OpenOrd/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Users/andy/Downloads/OpenOrd /Users/andy/Downloads/OpenOrd /Users/andy/Downloads/OpenOrd/build /Users/andy/Downloads/OpenOrd/build /Users/andy/Downloads/OpenOrd/build/CMakeFiles/OpenOrd.js.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/OpenOrd.js.dir/depend

