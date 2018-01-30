cmake_minimum_required(VERSION 2.8)

# Use clang++
# SET (CMAKE_CXX_COMPILER /usr/bin/clang++)

project(niepce CXX)

add_definitions("-std=c++11 -O2")

# set (OpenMP_C_FLAGS "-fopenmp")

find_package( OpenMP )
if (OPENMP_FOUND)
  set (CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${OpenMP_C_FLAGS}")
  set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${OpenMP_CXX_FLAGS}")
  set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} ${OpenMP_EXE_LINKER_FLAGS}")
  include_directories(SYSTEM ${OpenMP_INCLUDE_PATH})
endif()

# set (CMAKE_EXE_LINKER_FLAGS "-static-libgcc -static-libstdc++") # ok

add_subdirectory (random)
add_subdirectory (ext)
add_subdirectory (ext/tinyxml2)
add_subdirectory (core)
add_subdirectory (memory)
add_subdirectory (camera)
add_subdirectory (sampler)
add_subdirectory (shape)
add_subdirectory (texture)
add_subdirectory (bxdf)
add_subdirectory (material)
add_subdirectory (light)
add_subdirectory (primitive)
add_subdirectory (accelerator)
add_subdirectory (scene)
add_subdirectory (integrator)
add_subdirectory (test)


find_package (tinyxml2)

add_executable (
  niepce
  main/main.cc
)

target_link_libraries (
  niepce
  tinyxml2
  Integrator
  Scene
  Accelerator
  Primitive
  Light
  Material
  Bxdf
  Texture
  Shape
  Sampler
  # Camera
  Random
  Memory
  Core
)
