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
include CMakeFiles/off2off.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/off2off.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/off2off.dir/flags.make

CMakeFiles/off2off.dir/OffToOff_nc.cpp.o: CMakeFiles/off2off.dir/flags.make
CMakeFiles/off2off.dir/OffToOff_nc.cpp.o: OffToOff_nc.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/off2off.dir/OffToOff_nc.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/off2off.dir/OffToOff_nc.cpp.o -c /home/javier/Documentos/Memoria/format/OffToOff_nc.cpp

CMakeFiles/off2off.dir/OffToOff_nc.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/off2off.dir/OffToOff_nc.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/OffToOff_nc.cpp > CMakeFiles/off2off.dir/OffToOff_nc.cpp.i

CMakeFiles/off2off.dir/OffToOff_nc.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/off2off.dir/OffToOff_nc.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/OffToOff_nc.cpp -o CMakeFiles/off2off.dir/OffToOff_nc.cpp.s

CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.requires:

.PHONY : CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.requires

CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.provides: CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.requires
	$(MAKE) -f CMakeFiles/off2off.dir/build.make CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.provides.build
.PHONY : CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.provides

CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.provides.build: CMakeFiles/off2off.dir/OffToOff_nc.cpp.o


# Object files for target off2off
off2off_OBJECTS = \
"CMakeFiles/off2off.dir/OffToOff_nc.cpp.o"

# External object files for target off2off
off2off_EXTERNAL_OBJECTS = \
"/home/javier/Documentos/Memoria/geometry/Point.o" \
"/home/javier/Documentos/Memoria/geometry/Face.o" \
"/home/javier/Documentos/Memoria/geometry/FaceContainer.o" \
"/home/javier/Documentos/Memoria/read_write/ReadOff.o" \
"/home/javier/Documentos/Memoria/read_write/WriteOff.o"

off2off: CMakeFiles/off2off.dir/OffToOff_nc.cpp.o
off2off: /home/javier/Documentos/Memoria/geometry/Point.o
off2off: /home/javier/Documentos/Memoria/geometry/Face.o
off2off: /home/javier/Documentos/Memoria/geometry/FaceContainer.o
off2off: /home/javier/Documentos/Memoria/read_write/ReadOff.o
off2off: /home/javier/Documentos/Memoria/read_write/WriteOff.o
off2off: CMakeFiles/off2off.dir/build.make
off2off: CMakeFiles/off2off.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable off2off"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/off2off.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/off2off.dir/build: off2off

.PHONY : CMakeFiles/off2off.dir/build

CMakeFiles/off2off.dir/requires: CMakeFiles/off2off.dir/OffToOff_nc.cpp.o.requires

.PHONY : CMakeFiles/off2off.dir/requires

CMakeFiles/off2off.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/off2off.dir/cmake_clean.cmake
.PHONY : CMakeFiles/off2off.dir/clean

CMakeFiles/off2off.dir/depend:
	cd /home/javier/Documentos/Memoria/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format/CMakeFiles/off2off.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/off2off.dir/depend

