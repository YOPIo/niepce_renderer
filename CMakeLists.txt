cmake_minimum_required (VERSION 3.0)

# Project name
project (niepce)

# Use c++17 global options
set (CMAKE_CXX_FLAGS "-std=c++11 -pthread")

# Build options
# To building a plugin for autodesk maya, use "-DBUILD_MAYA_PLUGIN=on" option.
option (NI_USE_SIMD            "Enable to use SIMD." OFF)
option (BUILD_CUI_RENDERER     "Build a CUI renderer." ON)
option (BUILD_MAYA_PLUGIN      "Build a plugin for autodesk maya." OFF)
option (NIEPCE_FLOAT_IS_DOUBLE "" OFF)

# Generating a config file as "cmake_conifig.h"
configure_file (${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h)

if (USE_SIMD)
  message (STATUS "Use SIMD.")
  set (CMAKE_CXX_FLAGS "-msse4.1 -std=c++11 -pthread")
endif ()

if (BUILD_MAYA_PLUGIN)
  message (STATUS "Building a plugin for autodesk maya.")
  set (BUILD_CUI_RENDERER OFF)
  # Use FindMaya.cmake
  set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
  # Find the autodesk maya
  find_package (Maya REQUIRED)
else ()
  message (STATUS "Building a CUI renderer.")
endif ()

# Build static libraries
add_subdirectory (src/random)
add_subdirectory (src/bsdf)
add_subdirectory (src/renderer)
add_subdirectory (src/sampler)
add_subdirectory (src/light)
add_subdirectory (src/shape)
add_subdirectory (src/primitive)
add_subdirectory (src/texture)
add_subdirectory (src/material)
add_subdirectory (src/accelerator)
add_subdirectory (src/scene)
add_subdirectory (src/camera)
add_subdirectory (src/core)
add_subdirectory (src/ext)

# Add subdirectory to build the maya plugin
if (BUILD_MAYA_PLUGIN)
  add_subdirectory (src/maya)
  
else () # if (BUILD_CUI_RENDERER)
  add_executable (${PROJECT_NAME} src/main/main.cc)
  target_link_libraries (${PROJECT_NAME}
    Renderer
    Scene
    Accelerator
    Light
    Texture
    Material
    Camera
    Bsdf
    Shape
    Primitive
    Sampler
    Random
    Ext
    Core)

endif ()
