cmake_minimum_required (VERSION 3.5)


# Project name
project (niepce)


# Use c++11 global options
set (CMAKE_CXX_FLAGS "-std=c++11")


# Build options
# To building a plugin for autodesk maya, use "-DBUILD_MAYA_PLUGIN=on" option.
option (BUILD_MAYA_PLUGIN  "Build a plugin for autodesk maya." OFF)
option (BUILD_CUI_RENDERER "Build a CUI renderer." ON)


configure_file (${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h.in
                ${CMAKE_CURRENT_SOURCE_DIR}/cmake_config.h)


if (BUILD_MAYA_PLUGIN)
  message (STATUS "Building a plugin for autodesk maya.")
  # Use FindMaya.cmake
  set (CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/modules)
else ()
  message (STATUS "Building a CUI renderer.")
endif ()


# Build static libraries
add_subdirectory (src/core)


# Add subdirectory to build the maya plugin
if (BUILD_MAYA_PLUGIN)
  add_subdirectory (src/maya)
endif ()


if (!BUILD_MAYA_PLUGIN)
  add_executable (${PROJECT_NAME} src/main.cc)
else()

endif ()

target_link_libraries (${PROJECT_NAME} Core)
