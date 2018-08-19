cmake_minimum_required (VERSION 2.8)

# Crate static library
add_library (Shape STATIC
  shape.cc
  sphere.cc
  triangle.cc)
