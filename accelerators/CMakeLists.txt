#Version 3.0 at least
cmake_minimum_required(VERSION 3.0)

add_library(
  Accelerators STATIC
  bvh_node.cc
  bvh_bucket.cc
  bvh_primitive_info.cc
  bvh.cc
)
