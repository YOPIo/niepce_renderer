cmake_minimum_required (VERSION 3.5)

# Create static library6
add_library (Core STATIC
  bounds2.cc
  clipping_film.cc
  film.cc
  image.cc
  pixel.cc)
