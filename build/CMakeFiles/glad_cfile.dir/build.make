# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 4.0

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /Windir/Users/disco/personal/gravity_simulator

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /Windir/Users/disco/personal/gravity_simulator/build

# Include any dependencies generated for this target.
include CMakeFiles/glad_cfile.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include CMakeFiles/glad_cfile.dir/compiler_depend.make

# Include the progress variables for this target.
include CMakeFiles/glad_cfile.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/glad_cfile.dir/flags.make

CMakeFiles/glad_cfile.dir/codegen:
.PHONY : CMakeFiles/glad_cfile.dir/codegen

CMakeFiles/glad_cfile.dir/glad/src/glad.c.o: CMakeFiles/glad_cfile.dir/flags.make
CMakeFiles/glad_cfile.dir/glad/src/glad.c.o: /Windir/Users/disco/personal/gravity_simulator/glad/src/glad.c
CMakeFiles/glad_cfile.dir/glad/src/glad.c.o: CMakeFiles/glad_cfile.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=/Windir/Users/disco/personal/gravity_simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building C object CMakeFiles/glad_cfile.dir/glad/src/glad.c.o"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -MD -MT CMakeFiles/glad_cfile.dir/glad/src/glad.c.o -MF CMakeFiles/glad_cfile.dir/glad/src/glad.c.o.d -o CMakeFiles/glad_cfile.dir/glad/src/glad.c.o -c /Windir/Users/disco/personal/gravity_simulator/glad/src/glad.c

CMakeFiles/glad_cfile.dir/glad/src/glad.c.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing C source to CMakeFiles/glad_cfile.dir/glad/src/glad.c.i"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -E /Windir/Users/disco/personal/gravity_simulator/glad/src/glad.c > CMakeFiles/glad_cfile.dir/glad/src/glad.c.i

CMakeFiles/glad_cfile.dir/glad/src/glad.c.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling C source to assembly CMakeFiles/glad_cfile.dir/glad/src/glad.c.s"
	/usr/bin/cc $(C_DEFINES) $(C_INCLUDES) $(C_FLAGS) -S /Windir/Users/disco/personal/gravity_simulator/glad/src/glad.c -o CMakeFiles/glad_cfile.dir/glad/src/glad.c.s

# Object files for target glad_cfile
glad_cfile_OBJECTS = \
"CMakeFiles/glad_cfile.dir/glad/src/glad.c.o"

# External object files for target glad_cfile
glad_cfile_EXTERNAL_OBJECTS =

libglad_cfile.a: CMakeFiles/glad_cfile.dir/glad/src/glad.c.o
libglad_cfile.a: CMakeFiles/glad_cfile.dir/build.make
libglad_cfile.a: CMakeFiles/glad_cfile.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=/Windir/Users/disco/personal/gravity_simulator/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking C static library libglad_cfile.a"
	$(CMAKE_COMMAND) -P CMakeFiles/glad_cfile.dir/cmake_clean_target.cmake
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/glad_cfile.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/glad_cfile.dir/build: libglad_cfile.a
.PHONY : CMakeFiles/glad_cfile.dir/build

CMakeFiles/glad_cfile.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/glad_cfile.dir/cmake_clean.cmake
.PHONY : CMakeFiles/glad_cfile.dir/clean

CMakeFiles/glad_cfile.dir/depend:
	cd /Windir/Users/disco/personal/gravity_simulator/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /Windir/Users/disco/personal/gravity_simulator /Windir/Users/disco/personal/gravity_simulator /Windir/Users/disco/personal/gravity_simulator/build /Windir/Users/disco/personal/gravity_simulator/build /Windir/Users/disco/personal/gravity_simulator/build/CMakeFiles/glad_cfile.dir/DependInfo.cmake "--color=$(COLOR)"
.PHONY : CMakeFiles/glad_cfile.dir/depend

