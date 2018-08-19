cmake_minimum_required (VERSION 2.8)

add_library (Sampler STATIC
  sampler.cc
  random_sampler.cc
  low_discrepancy_sequence.cc
  hammersley.cc)
