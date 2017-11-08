cmake_minimum_required (VERSION 2.8)

add_library (
  Integrator STATIC
  integrator.cc
  sample_integrator.cc
  path_tracer.cc
  debug.cc
)
