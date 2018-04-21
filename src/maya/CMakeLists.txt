cmake_minimum_required (VERSION 3.5)

set (SOURCE_FILES "plugin_main.cc")

add_library (${PROJECT_NAME} SHARED ${SOURCE_FILES})
target_link_libraries (${PROJECT_NAME} PRIVATE Maya::Maya)
target_include_directories (${PROJECT_NAME} PRIVATE Maya::Maya)
MAYA_PLUGIN (${PROJECT_NAME})
