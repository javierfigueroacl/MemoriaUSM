# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.5

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
CMAKE_SOURCE_DIR = /home/javier/Documentos/Memoria/format

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/javier/Documentos/Memoria/format

# Include any dependencies generated for this target.
include CMakeFiles/joinoff.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/joinoff.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/joinoff.dir/flags.make

CMakeFiles/joinoff.dir/JoinPoint.cpp.o: CMakeFiles/joinoff.dir/flags.make
CMakeFiles/joinoff.dir/JoinPoint.cpp.o: JoinPoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/joinoff.dir/JoinPoint.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/joinoff.dir/JoinPoint.cpp.o -c /home/javier/Documentos/Memoria/format/JoinPoint.cpp

CMakeFiles/joinoff.dir/JoinPoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joinoff.dir/JoinPoint.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/JoinPoint.cpp > CMakeFiles/joinoff.dir/JoinPoint.cpp.i

CMakeFiles/joinoff.dir/JoinPoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joinoff.dir/JoinPoint.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/JoinPoint.cpp -o CMakeFiles/joinoff.dir/JoinPoint.cpp.s

CMakeFiles/joinoff.dir/JoinPoint.cpp.o.requires:

.PHONY : CMakeFiles/joinoff.dir/JoinPoint.cpp.o.requires

CMakeFiles/joinoff.dir/JoinPoint.cpp.o.provides: CMakeFiles/joinoff.dir/JoinPoint.cpp.o.requires
	$(MAKE) -f CMakeFiles/joinoff.dir/build.make CMakeFiles/joinoff.dir/JoinPoint.cpp.o.provides.build
.PHONY : CMakeFiles/joinoff.dir/JoinPoint.cpp.o.provides

CMakeFiles/joinoff.dir/JoinPoint.cpp.o.provides.build: CMakeFiles/joinoff.dir/JoinPoint.cpp.o


CMakeFiles/joinoff.dir/JoinOff.cpp.o: CMakeFiles/joinoff.dir/flags.make
CMakeFiles/joinoff.dir/JoinOff.cpp.o: JoinOff.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/joinoff.dir/JoinOff.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/joinoff.dir/JoinOff.cpp.o -c /home/javier/Documentos/Memoria/format/JoinOff.cpp

CMakeFiles/joinoff.dir/JoinOff.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joinoff.dir/JoinOff.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/JoinOff.cpp > CMakeFiles/joinoff.dir/JoinOff.cpp.i

CMakeFiles/joinoff.dir/JoinOff.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joinoff.dir/JoinOff.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/JoinOff.cpp -o CMakeFiles/joinoff.dir/JoinOff.cpp.s

CMakeFiles/joinoff.dir/JoinOff.cpp.o.requires:

.PHONY : CMakeFiles/joinoff.dir/JoinOff.cpp.o.requires

CMakeFiles/joinoff.dir/JoinOff.cpp.o.provides: CMakeFiles/joinoff.dir/JoinOff.cpp.o.requires
	$(MAKE) -f CMakeFiles/joinoff.dir/build.make CMakeFiles/joinoff.dir/JoinOff.cpp.o.provides.build
.PHONY : CMakeFiles/joinoff.dir/JoinOff.cpp.o.provides

CMakeFiles/joinoff.dir/JoinOff.cpp.o.provides.build: CMakeFiles/joinoff.dir/JoinOff.cpp.o


# Object files for target joinoff
joinoff_OBJECTS = \
"CMakeFiles/joinoff.dir/JoinPoint.cpp.o" \
"CMakeFiles/joinoff.dir/JoinOff.cpp.o"

# External object files for target joinoff
joinoff_EXTERNAL_OBJECTS = \
"/home/javier/Documentos/Memoria/geometry/Point.o" \
"/home/javier/Documentos/Memoria/geometry/Face.o" \
"/home/javier/Documentos/Memoria/geometry/FaceContainer.o" \
"/home/javier/Documentos/Memoria/read_write/ReadOff.o" \
"/home/javier/Documentos/Memoria/read_write/WriteOff.o"

joinoff: CMakeFiles/joinoff.dir/JoinPoint.cpp.o
joinoff: CMakeFiles/joinoff.dir/JoinOff.cpp.o
joinoff: /home/javier/Documentos/Memoria/geometry/Point.o
joinoff: /home/javier/Documentos/Memoria/geometry/Face.o
joinoff: /home/javier/Documentos/Memoria/geometry/FaceContainer.o
joinoff: /home/javier/Documentos/Memoria/read_write/ReadOff.o
joinoff: /home/javier/Documentos/Memoria/read_write/WriteOff.o
joinoff: CMakeFiles/joinoff.dir/build.make
joinoff: CMakeFiles/joinoff.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable joinoff"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joinoff.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/joinoff.dir/build: joinoff

.PHONY : CMakeFiles/joinoff.dir/build

CMakeFiles/joinoff.dir/requires: CMakeFiles/joinoff.dir/JoinPoint.cpp.o.requires
CMakeFiles/joinoff.dir/requires: CMakeFiles/joinoff.dir/JoinOff.cpp.o.requires

.PHONY : CMakeFiles/joinoff.dir/requires

CMakeFiles/joinoff.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/joinoff.dir/cmake_clean.cmake
.PHONY : CMakeFiles/joinoff.dir/clean

CMakeFiles/joinoff.dir/depend:
	cd /home/javier/Documentos/Memoria/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format/CMakeFiles/joinoff.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/joinoff.dir/depend
