cmake_minimum_required (VERSION 3.0)

# Create static library
add_library (Core STATIC
  assembled_tiles.cc
  bounds2f.cc
  tile.cc
  image.cc
  intersection.cc
  pixel.cc
  ray.cc
  render_settings.cc
  thread_pool.cc
  tile.cc
)
