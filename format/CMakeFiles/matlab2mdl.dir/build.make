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
include CMakeFiles/matlab2mdl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/matlab2mdl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/matlab2mdl.dir/flags.make

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o: CMakeFiles/matlab2mdl.dir/flags.make
CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o: MatlabToMdl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o -c /home/javier/Documentos/Memoria/format/MatlabToMdl.cpp

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/MatlabToMdl.cpp > CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.i

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/MatlabToMdl.cpp -o CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.s

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.requires:

.PHONY : CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.requires

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.provides: CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.requires
	$(MAKE) -f CMakeFiles/matlab2mdl.dir/build.make CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.provides.build
.PHONY : CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.provides

CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.provides.build: CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o


# Object files for target matlab2mdl
matlab2mdl_OBJECTS = \
"CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o"

# External object files for target matlab2mdl
matlab2mdl_EXTERNAL_OBJECTS = \
"/home/javier/Documentos/Memoria/geometry/Point.o" \
"/home/javier/Documentos/Memoria/geometry/Face.o" \
"/home/javier/Documentos/Memoria/geometry/FaceContainer.o" \
"/home/javier/Documentos/Memoria/read_write/ReadMatlab.o" \
"/home/javier/Documentos/Memoria/read_write/WriteMdl.o"

matlab2mdl: CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o
matlab2mdl: /home/javier/Documentos/Memoria/geometry/Point.o
matlab2mdl: /home/javier/Documentos/Memoria/geometry/Face.o
matlab2mdl: /home/javier/Documentos/Memoria/geometry/FaceContainer.o
matlab2mdl: /home/javier/Documentos/Memoria/read_write/ReadMatlab.o
matlab2mdl: /home/javier/Documentos/Memoria/read_write/WriteMdl.o
matlab2mdl: CMakeFiles/matlab2mdl.dir/build.make
matlab2mdl: CMakeFiles/matlab2mdl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable matlab2mdl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/matlab2mdl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/matlab2mdl.dir/build: matlab2mdl

.PHONY : CMakeFiles/matlab2mdl.dir/build

CMakeFiles/matlab2mdl.dir/requires: CMakeFiles/matlab2mdl.dir/MatlabToMdl.cpp.o.requires

.PHONY : CMakeFiles/matlab2mdl.dir/requires

CMakeFiles/matlab2mdl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/matlab2mdl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/matlab2mdl.dir/clean

CMakeFiles/matlab2mdl.dir/depend:
	cd /home/javier/Documentos/Memoria/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format/CMakeFiles/matlab2mdl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/matlab2mdl.dir/depend
