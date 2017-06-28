# Version 3.0 at least
cmake_minimum_required(VERSION 3.0)

#Use clang++, change default compiler to clang++, % export $CXX=clang++ before building
project(niepce CXX)

# CXX default options
set(CMAKE_CXX_FLAGS "-pthread -std=c++11 -O2")

# Show full logs when make
if(Debug)
  set(CMAKE_VERBOSE_MAKEFILE 1)
  set(CMAKE_CXX_FLAGS "-pthread -std=c++11 -O2 -DDebug")
endif(Debug)


# Load CMakeLists.txt from the following directories
add_subdirectory (accelerators)
add_subdirectory (cameras)
add_subdirectory (core)
add_subdirectory (geometries)
add_subdirectory (materials)
#add_subdirectory (memories)
add_subdirectory (primitives)
add_subdirectory (randoms)
add_subdirectory (scene)
add_subdirectory (shapes)
# add_subdirectory (spectrum)

add_executable(
  niepce
  bvh_test.cc
)

target_link_libraries(
  niepce
  Scene
  Shapes
  Cores
  Geometries
  Accelerators
  Cameras
  Materials
  Primitives
  Randoms
)
