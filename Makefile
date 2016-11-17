# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.6

# Default target executed when no arguments are given to make.
default_target: all

.PHONY : default_target

# Allow only one "make -f Makefile2" at a time, but pass parallelism.
.NOTPARALLEL:


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
CMAKE_COMMAND = /usr/local/Cellar/cmake/3.6.3/bin/cmake

# The command to remove a file.
RM = /usr/local/Cellar/cmake/3.6.3/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Users/andy/Workspace/OpenOrd.js

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Users/andy/Workspace/OpenOrd.js

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake cache editor..."
	/usr/local/Cellar/cmake/3.6.3/bin/ccmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/local/Cellar/cmake/3.6.3/bin/cmake -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/andy/Workspace/OpenOrd.js/CMakeFiles /Users/andy/Workspace/OpenOrd.js/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /Users/andy/Workspace/OpenOrd.js/CMakeFiles 0
.PHONY : all

# The main clean target
clean:
	$(MAKE) -f CMakeFiles/Makefile2 clean
.PHONY : clean

# The main clean target
clean/fast: clean

.PHONY : clean/fast

# Prepare targets for installation.
preinstall: all
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall

# Prepare targets for installation.
preinstall/fast:
	$(MAKE) -f CMakeFiles/Makefile2 preinstall
.PHONY : preinstall/fast

# clear depends
depend:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named OpenOrd

# Build rule for target.
OpenOrd: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 OpenOrd
.PHONY : OpenOrd

# fast build rule for target.
OpenOrd/fast:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/build
.PHONY : OpenOrd/fast

src/DensityGrid.o: src/DensityGrid.cpp.o

.PHONY : src/DensityGrid.o

# target to build an object file
src/DensityGrid.cpp.o:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/DensityGrid.cpp.o
.PHONY : src/DensityGrid.cpp.o

src/DensityGrid.i: src/DensityGrid.cpp.i

.PHONY : src/DensityGrid.i

# target to preprocess a source file
src/DensityGrid.cpp.i:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/DensityGrid.cpp.i
.PHONY : src/DensityGrid.cpp.i

src/DensityGrid.s: src/DensityGrid.cpp.s

.PHONY : src/DensityGrid.s

# target to generate assembly for a file
src/DensityGrid.cpp.s:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/DensityGrid.cpp.s
.PHONY : src/DensityGrid.cpp.s

src/graph.o: src/graph.cpp.o

.PHONY : src/graph.o

# target to build an object file
src/graph.cpp.o:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/graph.cpp.o
.PHONY : src/graph.cpp.o

src/graph.i: src/graph.cpp.i

.PHONY : src/graph.i

# target to preprocess a source file
src/graph.cpp.i:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/graph.cpp.i
.PHONY : src/graph.cpp.i

src/graph.s: src/graph.cpp.s

.PHONY : src/graph.s

# target to generate assembly for a file
src/graph.cpp.s:
	$(MAKE) -f CMakeFiles/OpenOrd.dir/build.make CMakeFiles/OpenOrd.dir/src/graph.cpp.s
.PHONY : src/graph.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... edit_cache"
	@echo "... rebuild_cache"
	@echo "... OpenOrd"
	@echo "... src/DensityGrid.o"
	@echo "... src/DensityGrid.i"
	@echo "... src/DensityGrid.s"
	@echo "... src/graph.o"
	@echo "... src/graph.i"
	@echo "... src/graph.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -H$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system
