# CMAKE generated file: DO NOT EDIT!
# Generated by "MinGW Makefiles" Generator, CMake Version 3.30

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

SHELL = cmd.exe

# The CMake executable.
CMAKE_COMMAND = D:\usefulTools\Cmake\bin\cmake.exe

# The command to remove a file.
RM = D:\usefulTools\Cmake\bin\cmake.exe -E rm -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = D:\Git_Project\github\MachineVisionWin

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = D:\Git_Project\github\MachineVisionWin\build

# Include any dependencies generated for this target.
include Hessian/CMakeFiles/LibFrangi.dir/depend.make
# Include any dependencies generated by the compiler for this target.
include Hessian/CMakeFiles/LibFrangi.dir/compiler_depend.make

# Include the progress variables for this target.
include Hessian/CMakeFiles/LibFrangi.dir/progress.make

# Include the compile flags for this target's objects.
include Hessian/CMakeFiles/LibFrangi.dir/flags.make

Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj: Hessian/CMakeFiles/LibFrangi.dir/flags.make
Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj: Hessian/CMakeFiles/LibFrangi.dir/includes_CXX.rsp
Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj: D:/Git_Project/github/MachineVisionWin/Hessian/src/frangi.cpp
Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj: Hessian/CMakeFiles/LibFrangi.dir/compiler_depend.ts
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --progress-dir=D:\Git_Project\github\MachineVisionWin\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_1) "Building CXX object Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj"
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && D:\usefulTools\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -MD -MT Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj -MF CMakeFiles\LibFrangi.dir\src\frangi.cpp.obj.d -o CMakeFiles\LibFrangi.dir\src\frangi.cpp.obj -c D:\Git_Project\github\MachineVisionWin\Hessian\src\frangi.cpp

Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.i: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Preprocessing CXX source to CMakeFiles/LibFrangi.dir/src/frangi.cpp.i"
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && D:\usefulTools\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -E D:\Git_Project\github\MachineVisionWin\Hessian\src\frangi.cpp > CMakeFiles\LibFrangi.dir\src\frangi.cpp.i

Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.s: cmake_force
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green "Compiling CXX source to assembly CMakeFiles/LibFrangi.dir/src/frangi.cpp.s"
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && D:\usefulTools\MinGW\mingw64\bin\c++.exe $(CXX_DEFINES) $(CXX_INCLUDES) $(CXX_FLAGS) -S D:\Git_Project\github\MachineVisionWin\Hessian\src\frangi.cpp -o CMakeFiles\LibFrangi.dir\src\frangi.cpp.s

# Object files for target LibFrangi
LibFrangi_OBJECTS = \
"CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj"

# External object files for target LibFrangi
LibFrangi_EXTERNAL_OBJECTS =

Hessian/libLibFrangi.a: Hessian/CMakeFiles/LibFrangi.dir/src/frangi.cpp.obj
Hessian/libLibFrangi.a: Hessian/CMakeFiles/LibFrangi.dir/build.make
Hessian/libLibFrangi.a: Hessian/CMakeFiles/LibFrangi.dir/link.txt
	@$(CMAKE_COMMAND) -E cmake_echo_color "--switch=$(COLOR)" --green --bold --progress-dir=D:\Git_Project\github\MachineVisionWin\build\CMakeFiles --progress-num=$(CMAKE_PROGRESS_2) "Linking CXX static library libLibFrangi.a"
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && $(CMAKE_COMMAND) -P CMakeFiles\LibFrangi.dir\cmake_clean_target.cmake
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && $(CMAKE_COMMAND) -E cmake_link_script CMakeFiles\LibFrangi.dir\link.txt --verbose=$(VERBOSE)

# Rule to build all files generated by this target.
Hessian/CMakeFiles/LibFrangi.dir/build: Hessian/libLibFrangi.a
.PHONY : Hessian/CMakeFiles/LibFrangi.dir/build

Hessian/CMakeFiles/LibFrangi.dir/clean:
	cd /d D:\Git_Project\github\MachineVisionWin\build\Hessian && $(CMAKE_COMMAND) -P CMakeFiles\LibFrangi.dir\cmake_clean.cmake
.PHONY : Hessian/CMakeFiles/LibFrangi.dir/clean

Hessian/CMakeFiles/LibFrangi.dir/depend:
	$(CMAKE_COMMAND) -E cmake_depends "MinGW Makefiles" D:\Git_Project\github\MachineVisionWin D:\Git_Project\github\MachineVisionWin\Hessian D:\Git_Project\github\MachineVisionWin\build D:\Git_Project\github\MachineVisionWin\build\Hessian D:\Git_Project\github\MachineVisionWin\build\Hessian\CMakeFiles\LibFrangi.dir\DependInfo.cmake "--color=$(COLOR)"
.PHONY : Hessian/CMakeFiles/LibFrangi.dir/depend

