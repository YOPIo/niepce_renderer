cmake_minimum_required(VERSION 3.1)

project(niepce)

add_definitions("-std=c++1y")

add_subdirectory(core)
add_subdirectory(camera)
add_subdirectory(geometry)
add_subdirectory(image)
add_subdirectory(material)
add_subdirectory(random)
add_subdirectory(texture)

add_executable(niepce main.cc)

target_link_libraries(niepce core)
target_link_libraries(niepce material)
target_link_libraries(niepce geometry)
target_link_libraries(niepce camera)
target_link_libraries(niepce image)
target_link_libraries(niepce random)
target_link_libraries(niepce texture)
target_link_libraries(niepce core)


