cmake_minimum_required (VERSION 2.8)

# Create static library
add_library (Renderer STATIC
  renderer.cc
  path_tracer.cc)
