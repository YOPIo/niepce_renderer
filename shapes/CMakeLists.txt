# Version 3.0 at least
cmake_minimum_required(VERSION 3.0)

add_library(Shapes STATIC
  vertex.cc
  shape.cc
  sphere.cc
  triangle_mesh.cc
  triangle.cc
)
