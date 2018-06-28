cmake_minimum_required (VERSION 2.8)

# Crate static library
add_library (Math STATIC
  point2f.cc
  point3f.cc
  vector2f.cc
  vector3f.cc)
