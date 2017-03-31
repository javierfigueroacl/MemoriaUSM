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
include CMakeFiles/joinmdl.dir/depend.make

# Include the progress variables for this target.
include CMakeFiles/joinmdl.dir/progress.make

# Include the compile flags for this target's objects.
include CMakeFiles/joinmdl.dir/flags.make

CMakeFiles/joinmdl.dir/JoinPoint.cpp.o: CMakeFiles/joinmdl.dir/flags.make
CMakeFiles/joinmdl.dir/JoinPoint.cpp.o: JoinPoint.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object CMakeFiles/joinmdl.dir/JoinPoint.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/joinmdl.dir/JoinPoint.cpp.o -c /home/javier/Documentos/Memoria/format/JoinPoint.cpp

CMakeFiles/joinmdl.dir/JoinPoint.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joinmdl.dir/JoinPoint.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/JoinPoint.cpp > CMakeFiles/joinmdl.dir/JoinPoint.cpp.i

CMakeFiles/joinmdl.dir/JoinPoint.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joinmdl.dir/JoinPoint.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/JoinPoint.cpp -o CMakeFiles/joinmdl.dir/JoinPoint.cpp.s

CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.requires:

.PHONY : CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.requires

CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.provides: CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.requires
	$(MAKE) -f CMakeFiles/joinmdl.dir/build.make CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.provides.build
.PHONY : CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.provides

CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.provides.build: CMakeFiles/joinmdl.dir/JoinPoint.cpp.o


CMakeFiles/joinmdl.dir/JoinMdl.cpp.o: CMakeFiles/joinmdl.dir/flags.make
CMakeFiles/joinmdl.dir/JoinMdl.cpp.o: JoinMdl.cpp
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Building CXX object CMakeFiles/joinmdl.dir/JoinMdl.cpp.o"
	/usr/bin/c++   $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -o CMakeFiles/joinmdl.dir/JoinMdl.cpp.o -c /home/javier/Documentos/Memoria/format/JoinMdl.cpp

CMakeFiles/joinmdl.dir/JoinMdl.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Preprocessing CXX source to CMakeFiles/joinmdl.dir/JoinMdl.cpp.i"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E /home/javier/Documentos/Memoria/format/JoinMdl.cpp > CMakeFiles/joinmdl.dir/JoinMdl.cpp.i

CMakeFiles/joinmdl.dir/JoinMdl.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green "Compiling CXX source to assembly CMakeFiles/joinmdl.dir/JoinMdl.cpp.s"
	/usr/bin/c++  $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S /home/javier/Documentos/Memoria/format/JoinMdl.cpp -o CMakeFiles/joinmdl.dir/JoinMdl.cpp.s

CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.requires:

.PHONY : CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.requires

CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.provides: CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.requires
	$(MAKE) -f CMakeFiles/joinmdl.dir/build.make CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.provides.build
.PHONY : CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.provides

CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.provides.build: CMakeFiles/joinmdl.dir/JoinMdl.cpp.o


# Object files for target joinmdl
joinmdl_OBJECTS = \
"CMakeFiles/joinmdl.dir/JoinPoint.cpp.o" \
"CMakeFiles/joinmdl.dir/JoinMdl.cpp.o"

# External object files for target joinmdl
joinmdl_EXTERNAL_OBJECTS = \
"/home/javier/Documentos/Memoria/geometry/Point.o" \
"/home/javier/Documentos/Memoria/geometry/Face.o" \
"/home/javier/Documentos/Memoria/geometry/FaceContainer.o" \
"/home/javier/Documentos/Memoria/read_write/ReadMdl.o" \
"/home/javier/Documentos/Memoria/read_write/WriteMdl.o"

joinmdl: CMakeFiles/joinmdl.dir/JoinPoint.cpp.o
joinmdl: CMakeFiles/joinmdl.dir/JoinMdl.cpp.o
joinmdl: /home/javier/Documentos/Memoria/geometry/Point.o
joinmdl: /home/javier/Documentos/Memoria/geometry/Face.o
joinmdl: /home/javier/Documentos/Memoria/geometry/FaceContainer.o
joinmdl: /home/javier/Documentos/Memoria/read_write/ReadMdl.o
joinmdl: /home/javier/Documentos/Memoria/read_write/WriteMdl.o
joinmdl: CMakeFiles/joinmdl.dir/build.make
joinmdl: CMakeFiles/joinmdl.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --green --bold --progress-dir=/home/javier/Documentos/Memoria/format/CMakeFiles --progress-num=$(CMAKE_PROGRESS_3) "Linking CXX executable joinmdl"
	$(CMAKE_COMMAND) -E cmake_link_script CMakeFiles/joinmdl.dir/link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
CMakeFiles/joinmdl.dir/build: joinmdl

.PHONY : CMakeFiles/joinmdl.dir/build

CMakeFiles/joinmdl.dir/requires: CMakeFiles/joinmdl.dir/JoinPoint.cpp.o.requires
CMakeFiles/joinmdl.dir/requires: CMakeFiles/joinmdl.dir/JoinMdl.cpp.o.requires

.PHONY : CMakeFiles/joinmdl.dir/requires

CMakeFiles/joinmdl.dir/clean:
	$(CMAKE_COMMAND) -P CMakeFiles/joinmdl.dir/cmake_clean.cmake
.PHONY : CMakeFiles/joinmdl.dir/clean

CMakeFiles/joinmdl.dir/depend:
	cd /home/javier/Documentos/Memoria/format && $(CMAKE_COMMAND) -E cmake_depends "Unix Makefiles" /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format /home/javier/Documentos/Memoria/format/CMakeFiles/joinmdl.dir/DependInfo.cmake --color=$(COLOR)
.PHONY : CMakeFiles/joinmdl.dir/depend

