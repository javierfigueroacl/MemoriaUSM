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
include CMakeFiles/mesh2mdl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/mesh2mdl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/mesh2mdl.dir/flags.make

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o: CMakeFiles/mesh2mdl.dir/flags.make
CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o: MeshToMdl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o -c /home/javier/Documentos/Memoria/format/MeshToMdl.cpp

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/MeshToMdl.cpp > CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.i

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/MeshToMdl.cpp -o CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.s

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.requires:

.PHONY : CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.requires

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.provides: CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.requires
	$(MAKE) -f CMakeFiles/mesh2mdl.dir/build.make CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.provides.build
.PHONY : CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.provides

CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.provides.build: CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o


# Object files for target mesh2mdl
mesh2mdl_OBJECTS = \
"CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o"

# External object files for target mesh2mdl
mesh2mdl_EXTERNAL_OBJECTS = \
"/home/javier/Documentos/Memoria/geometry/Point.o" \
"/home/javier/Documentos/Memoria/geometry/Face.o" \
"/home/javier/Documentos/Memoria/geometry/FaceContainer.o" \
"/home/javier/Documentos/Memoria/read_write/ReadMeshSurface.o" \
"/home/javier/Documentos/Memoria/read_write/WriteMdl.o"

mesh2mdl: CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o
mesh2mdl: /home/javier/Documentos/Memoria/geometry/Point.o
mesh2mdl: /home/javier/Documentos/Memoria/geometry/Face.o
mesh2mdl: /home/javier/Documentos/Memoria/geometry/FaceContainer.o
mesh2mdl: /home/javier/Documentos/Memoria/read_write/ReadMeshSurface.o
mesh2mdl: /home/javier/Documentos/Memoria/read_write/WriteMdl.o
mesh2mdl: CMakeFiles/mesh2mdl.dir/build.make
mesh2mdl: CMakeFiles/mesh2mdl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX executable mesh2mdl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/mesh2mdl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/mesh2mdl.dir/build: mesh2mdl

.PHONY : CMakeFiles/mesh2mdl.dir/build

CMakeFiles/mesh2mdl.dir/requires: CMakeFiles/mesh2mdl.dir/MeshToMdl.cpp.o.requires

.PHONY : CMakeFiles/mesh2mdl.dir/requires

CMakeFiles/mesh2mdl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/mesh2mdl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/mesh2mdl.dir/clean

CMakeFiles/mesh2mdl.dir/depend:
	cd /home/javier/Documentos/Memoria/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format/CMakeFiles/mesh2mdl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/mesh2mdl.dir/depend

