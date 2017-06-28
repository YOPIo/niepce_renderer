#Version 3.0 at least
cmake_minimum_required(VERSION 3.0)

add_library(
  Geometries STATIC
  boundingbox2.cc
  boundingbox3.cc
  matrix4x4.cc
  normal3.cc
  point2.cc
  point3.cc
  point4.cc
  ray.cc
  vector2.cc
  vector3.cc
  vector4.cc
)
