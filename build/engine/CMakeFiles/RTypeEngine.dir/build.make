# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.22

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
CMAKE_SOURCE_DIR = /root/projets/RType

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /root/projets/RType/build

# Include any dependencies generated for this target.
include engine/CMakeFiles/RTypeEngine.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include engine/CMakeFiles/RTypeEngine.dir/compiler_depend.make

# Include the progress variables for this target.
include engine/CMakeFiles/RTypeEngine.dir/progress.make

# Include the compile flags for this target's objects.
include engine/CMakeFiles/RTypeEngine.dir/flags.make

engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o: engine/CMakeFiles/RTypeEngine.dir/flags.make
engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o: ../engine/src/RTypeEngine.cpp
engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o: engine/CMakeFiles/RTypeEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/projets/RType/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o -MF CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o.d -o CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o -c /root/projets/RType/engine/src/RTypeEngine.cpp

engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.i"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/projets/RType/engine/src/RTypeEngine.cpp > CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.i

engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.s"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/projets/RType/engine/src/RTypeEngine.cpp -o CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.s

engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o: engine/CMakeFiles/RTypeEngine.dir/flags.make
engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o: ../engine/src/RenderSystem/RenderSystem.cpp
engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o: engine/CMakeFiles/RTypeEngine.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/root/projets/RType/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o -MF CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o.d -o CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o -c /root/projets/RType/engine/src/RenderSystem/RenderSystem.cpp

engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.i"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /root/projets/RType/engine/src/RenderSystem/RenderSystem.cpp > CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.i

engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.s"
	cd /root/projets/RType/build/engine && /usr/bin/c++ $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /root/projets/RType/engine/src/RenderSystem/RenderSystem.cpp -o CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.s

# Object files for target RTypeEngine
RTypeEngine_OBJECTS = \
"CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o" \
"CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o"

# External object files for target RTypeEngine
RTypeEngine_EXTERNAL_OBJECTS =

engine/libRTypeEngine.a: engine/CMakeFiles/RTypeEngine.dir/src/RTypeEngine.cpp.o
engine/libRTypeEngine.a: engine/CMakeFiles/RTypeEngine.dir/src/RenderSystem/RenderSystem.cpp.o
engine/libRTypeEngine.a: engine/CMakeFiles/RTypeEngine.dir/build.make
engine/libRTypeEngine.a: engine/CMakeFiles/RTypeEngine.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/root/projets/RType/build/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX static library libRTypeEngine.a"
	cd /root/projets/RType/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/RTypeEngine.dir/cmake_clean_target.cmake
	cd /root/projets/RType/build/engine && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/RTypeEngine.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
engine/CMakeFiles/RTypeEngine.dir/build: engine/libRTypeEngine.a
.PHONY : engine/CMakeFiles/RTypeEngine.dir/build

engine/CMakeFiles/RTypeEngine.dir/clean:
	cd /root/projets/RType/build/engine && $(CMAKE_COMMAND) -P CMakeFiles/RTypeEngine.dir/cmake_clean.cmake
.PHONY : engine/CMakeFiles/RTypeEngine.dir/clean

engine/CMakeFiles/RTypeEngine.dir/depend:
	cd /root/projets/RType/build && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /root/projets/RType /root/projets/RType/engine /root/projets/RType/build /root/projets/RType/build/engine /root/projets/RType/build/engine/CMakeFiles/RTypeEngine.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : engine/CMakeFiles/RTypeEngine.dir/depend

