cmake_minimum_required (VERSION 3.0)

add_library (Sampler STATIC
  sampler.cc
  random_sampler.cc
  low_discrepancy_sequence.cc)
