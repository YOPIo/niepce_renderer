cmake_minimum_required (VERSION 2.8)

add_library(
  Core STATIC
  object.cc
  image.cc
  pixel.cc
  geometry.cc
  matrix4x4.cc
  transform.cc
)
