cmake_minimum_required(VERSION 3.1)

add_library(camera STATIC
                   camera.cc
                   pinhole_camera.cc
                   image_sensor.cc
)
