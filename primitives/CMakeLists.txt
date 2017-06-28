# Version 3.0 at least
cmake_minimum_required(VERSION 3.0)

add_library(Primitives STATIC
  primitive.cc
  aggregate_primitive.cc
  geometric_primitive.cc)
