cmake_minimum_required(VERSION 3.1)

add_library(geometry STATIC
                     face.cc
                     geometry.cc
                     sphere.cc
                     triangle.cc
                     vertex.cc
)
