cmake_minimum_required (VERSION 3.0)

# Create static library
add_library (Core STATIC
  assembled_tiles.cc
  tile.cc
  image.cc
  pixel.cc
)
