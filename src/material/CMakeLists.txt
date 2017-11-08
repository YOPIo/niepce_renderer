cmake_minimum_required (VERSION 2.8)

add_library(
  Material STATIC
  material.cc
  matte.cc
  mirror.cc
  microfacet_test.cc
  glass.cc
)
