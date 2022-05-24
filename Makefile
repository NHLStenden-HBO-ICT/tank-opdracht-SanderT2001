# CMAKE generated file: DO NOT EDIT!
# Generated by "Unix Makefiles" Generator, CMake Version 3.16

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
CMAKE_COMMAND = /usr/bin/cmake

# The command to remove a file.
RM = /usr/bin/cmake -E remove -f

# Escaping for special characters.
EQUALS = =

# The top-level source directory on which CMake was run.
CMAKE_SOURCE_DIR = /home/sandertuinstra/projects/code/cpp/tank-opdracht-SanderT2001

# The top-level build directory on which CMake was run.
CMAKE_BINARY_DIR = /home/sandertuinstra/projects/code/cpp/tank-opdracht-SanderT2001

#=============================================================================
# Targets provided globally by CMake.

# Special rule for the target rebuild_cache
rebuild_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "Running CMake to regenerate build system..."
	/usr/bin/cmake -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR)
.PHONY : rebuild_cache

# Special rule for the target rebuild_cache
rebuild_cache/fast: rebuild_cache

.PHONY : rebuild_cache/fast

# Special rule for the target edit_cache
edit_cache:
	@$(CMAKE_COMMAND) -E cmake_echo_color --switch=$(COLOR) --cyan "No interactive CMake dialog available..."
	/usr/bin/cmake -E echo No\ interactive\ CMake\ dialog\ available.
.PHONY : edit_cache

# Special rule for the target edit_cache
edit_cache/fast: edit_cache

.PHONY : edit_cache/fast

# The main all target
all: cmake_check_build_system
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sandertuinstra/projects/code/cpp/tank-opdracht-SanderT2001/CMakeFiles /home/sandertuinstra/projects/code/cpp/tank-opdracht-SanderT2001/CMakeFiles/progress.marks
	$(MAKE) -f CMakeFiles/Makefile2 all
	$(CMAKE_COMMAND) -E cmake_progress_start /home/sandertuinstra/projects/code/cpp/tank-opdracht-SanderT2001/CMakeFiles 0
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
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 1
.PHONY : depend

#=============================================================================
# Target rules for targets named Tmpl8_2018-01

# Build rule for target.
Tmpl8_2018-01: cmake_check_build_system
	$(MAKE) -f CMakeFiles/Makefile2 Tmpl8_2018-01
.PHONY : Tmpl8_2018-01

# fast build rule for target.
Tmpl8_2018-01/fast:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/build
.PHONY : Tmpl8_2018-01/fast

explosion.o: explosion.cpp.o

.PHONY : explosion.o

# target to build an object file
explosion.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/explosion.cpp.o
.PHONY : explosion.cpp.o

explosion.i: explosion.cpp.i

.PHONY : explosion.i

# target to preprocess a source file
explosion.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/explosion.cpp.i
.PHONY : explosion.cpp.i

explosion.s: explosion.cpp.s

.PHONY : explosion.s

# target to generate assembly for a file
explosion.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/explosion.cpp.s
.PHONY : explosion.cpp.s

game.o: game.cpp.o

.PHONY : game.o

# target to build an object file
game.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/game.cpp.o
.PHONY : game.cpp.o

game.i: game.cpp.i

.PHONY : game.i

# target to preprocess a source file
game.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/game.cpp.i
.PHONY : game.cpp.i

game.s: game.cpp.s

.PHONY : game.s

# target to generate assembly for a file
game.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/game.cpp.s
.PHONY : game.cpp.s

grid.o: grid.cpp.o

.PHONY : grid.o

# target to build an object file
grid.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/grid.cpp.o
.PHONY : grid.cpp.o

grid.i: grid.cpp.i

.PHONY : grid.i

# target to preprocess a source file
grid.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/grid.cpp.i
.PHONY : grid.cpp.i

grid.s: grid.cpp.s

.PHONY : grid.s

# target to generate assembly for a file
grid.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/grid.cpp.s
.PHONY : grid.cpp.s

gridaddtankcommand.o: gridaddtankcommand.cpp.o

.PHONY : gridaddtankcommand.o

# target to build an object file
gridaddtankcommand.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridaddtankcommand.cpp.o
.PHONY : gridaddtankcommand.cpp.o

gridaddtankcommand.i: gridaddtankcommand.cpp.i

.PHONY : gridaddtankcommand.i

# target to preprocess a source file
gridaddtankcommand.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridaddtankcommand.cpp.i
.PHONY : gridaddtankcommand.cpp.i

gridaddtankcommand.s: gridaddtankcommand.cpp.s

.PHONY : gridaddtankcommand.s

# target to generate assembly for a file
gridaddtankcommand.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridaddtankcommand.cpp.s
.PHONY : gridaddtankcommand.cpp.s

gridcell.o: gridcell.cpp.o

.PHONY : gridcell.o

# target to build an object file
gridcell.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridcell.cpp.o
.PHONY : gridcell.cpp.o

gridcell.i: gridcell.cpp.i

.PHONY : gridcell.i

# target to preprocess a source file
gridcell.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridcell.cpp.i
.PHONY : gridcell.cpp.i

gridcell.s: gridcell.cpp.s

.PHONY : gridcell.s

# target to generate assembly for a file
gridcell.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridcell.cpp.s
.PHONY : gridcell.cpp.s

gridedittankcommand.o: gridedittankcommand.cpp.o

.PHONY : gridedittankcommand.o

# target to build an object file
gridedittankcommand.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridedittankcommand.cpp.o
.PHONY : gridedittankcommand.cpp.o

gridedittankcommand.i: gridedittankcommand.cpp.i

.PHONY : gridedittankcommand.i

# target to preprocess a source file
gridedittankcommand.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridedittankcommand.cpp.i
.PHONY : gridedittankcommand.cpp.i

gridedittankcommand.s: gridedittankcommand.cpp.s

.PHONY : gridedittankcommand.s

# target to generate assembly for a file
gridedittankcommand.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/gridedittankcommand.cpp.s
.PHONY : gridedittankcommand.cpp.s

kdnode.o: kdnode.cpp.o

.PHONY : kdnode.o

# target to build an object file
kdnode.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdnode.cpp.o
.PHONY : kdnode.cpp.o

kdnode.i: kdnode.cpp.i

.PHONY : kdnode.i

# target to preprocess a source file
kdnode.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdnode.cpp.i
.PHONY : kdnode.cpp.i

kdnode.s: kdnode.cpp.s

.PHONY : kdnode.s

# target to generate assembly for a file
kdnode.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdnode.cpp.s
.PHONY : kdnode.cpp.s

kdtree.o: kdtree.cpp.o

.PHONY : kdtree.o

# target to build an object file
kdtree.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdtree.cpp.o
.PHONY : kdtree.cpp.o

kdtree.i: kdtree.cpp.i

.PHONY : kdtree.i

# target to preprocess a source file
kdtree.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdtree.cpp.i
.PHONY : kdtree.cpp.i

kdtree.s: kdtree.cpp.s

.PHONY : kdtree.s

# target to generate assembly for a file
kdtree.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/kdtree.cpp.s
.PHONY : kdtree.cpp.s

particle_beam.o: particle_beam.cpp.o

.PHONY : particle_beam.o

# target to build an object file
particle_beam.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/particle_beam.cpp.o
.PHONY : particle_beam.cpp.o

particle_beam.i: particle_beam.cpp.i

.PHONY : particle_beam.i

# target to preprocess a source file
particle_beam.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/particle_beam.cpp.i
.PHONY : particle_beam.cpp.i

particle_beam.s: particle_beam.cpp.s

.PHONY : particle_beam.s

# target to generate assembly for a file
particle_beam.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/particle_beam.cpp.s
.PHONY : particle_beam.cpp.s

rocket.o: rocket.cpp.o

.PHONY : rocket.o

# target to build an object file
rocket.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/rocket.cpp.o
.PHONY : rocket.cpp.o

rocket.i: rocket.cpp.i

.PHONY : rocket.i

# target to preprocess a source file
rocket.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/rocket.cpp.i
.PHONY : rocket.cpp.i

rocket.s: rocket.cpp.s

.PHONY : rocket.s

# target to generate assembly for a file
rocket.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/rocket.cpp.s
.PHONY : rocket.cpp.s

smoke.o: smoke.cpp.o

.PHONY : smoke.o

# target to build an object file
smoke.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/smoke.cpp.o
.PHONY : smoke.cpp.o

smoke.i: smoke.cpp.i

.PHONY : smoke.i

# target to preprocess a source file
smoke.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/smoke.cpp.i
.PHONY : smoke.cpp.i

smoke.s: smoke.cpp.s

.PHONY : smoke.s

# target to generate assembly for a file
smoke.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/smoke.cpp.s
.PHONY : smoke.cpp.s

surface.o: surface.cpp.o

.PHONY : surface.o

# target to build an object file
surface.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/surface.cpp.o
.PHONY : surface.cpp.o

surface.i: surface.cpp.i

.PHONY : surface.i

# target to preprocess a source file
surface.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/surface.cpp.i
.PHONY : surface.cpp.i

surface.s: surface.cpp.s

.PHONY : surface.s

# target to generate assembly for a file
surface.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/surface.cpp.s
.PHONY : surface.cpp.s

tank.o: tank.cpp.o

.PHONY : tank.o

# target to build an object file
tank.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/tank.cpp.o
.PHONY : tank.cpp.o

tank.i: tank.cpp.i

.PHONY : tank.i

# target to preprocess a source file
tank.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/tank.cpp.i
.PHONY : tank.cpp.i

tank.s: tank.cpp.s

.PHONY : tank.s

# target to generate assembly for a file
tank.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/tank.cpp.s
.PHONY : tank.cpp.s

template.o: template.cpp.o

.PHONY : template.o

# target to build an object file
template.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/template.cpp.o
.PHONY : template.cpp.o

template.i: template.cpp.i

.PHONY : template.i

# target to preprocess a source file
template.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/template.cpp.i
.PHONY : template.cpp.i

template.s: template.cpp.s

.PHONY : template.s

# target to generate assembly for a file
template.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/template.cpp.s
.PHONY : template.cpp.s

terrain.o: terrain.cpp.o

.PHONY : terrain.o

# target to build an object file
terrain.cpp.o:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/terrain.cpp.o
.PHONY : terrain.cpp.o

terrain.i: terrain.cpp.i

.PHONY : terrain.i

# target to preprocess a source file
terrain.cpp.i:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/terrain.cpp.i
.PHONY : terrain.cpp.i

terrain.s: terrain.cpp.s

.PHONY : terrain.s

# target to generate assembly for a file
terrain.cpp.s:
	$(MAKE) -f CMakeFiles/Tmpl8_2018-01.dir/build.make CMakeFiles/Tmpl8_2018-01.dir/terrain.cpp.s
.PHONY : terrain.cpp.s

# Help Target
help:
	@echo "The following are some of the valid targets for this Makefile:"
	@echo "... all (the default if no target is provided)"
	@echo "... clean"
	@echo "... depend"
	@echo "... rebuild_cache"
	@echo "... edit_cache"
	@echo "... Tmpl8_2018-01"
	@echo "... explosion.o"
	@echo "... explosion.i"
	@echo "... explosion.s"
	@echo "... game.o"
	@echo "... game.i"
	@echo "... game.s"
	@echo "... grid.o"
	@echo "... grid.i"
	@echo "... grid.s"
	@echo "... gridaddtankcommand.o"
	@echo "... gridaddtankcommand.i"
	@echo "... gridaddtankcommand.s"
	@echo "... gridcell.o"
	@echo "... gridcell.i"
	@echo "... gridcell.s"
	@echo "... gridedittankcommand.o"
	@echo "... gridedittankcommand.i"
	@echo "... gridedittankcommand.s"
	@echo "... kdnode.o"
	@echo "... kdnode.i"
	@echo "... kdnode.s"
	@echo "... kdtree.o"
	@echo "... kdtree.i"
	@echo "... kdtree.s"
	@echo "... particle_beam.o"
	@echo "... particle_beam.i"
	@echo "... particle_beam.s"
	@echo "... rocket.o"
	@echo "... rocket.i"
	@echo "... rocket.s"
	@echo "... smoke.o"
	@echo "... smoke.i"
	@echo "... smoke.s"
	@echo "... surface.o"
	@echo "... surface.i"
	@echo "... surface.s"
	@echo "... tank.o"
	@echo "... tank.i"
	@echo "... tank.s"
	@echo "... template.o"
	@echo "... template.i"
	@echo "... template.s"
	@echo "... terrain.o"
	@echo "... terrain.i"
	@echo "... terrain.s"
.PHONY : help



#=============================================================================
# Special targets to cleanup operation of make.

# Special rule to run CMake to check the build system integrity.
# No rule that depends on this can have commands that come from listfiles
# because they might be regenerated.
cmake_check_build_system:
	$(CMAKE_COMMAND) -S$(CMAKE_SOURCE_DIR) -B$(CMAKE_BINARY_DIR) --check-build-system CMakeFiles/Makefile.cmake 0
.PHONY : cmake_check_build_system

