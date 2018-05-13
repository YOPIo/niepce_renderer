cmake_minimum_required (VERSION 3.0)

# Create static library
add_library (Core STATIC
  assembled_tiles.cc
  bounds2f.cc
  tile.cc
  image.cc
  ioimage.cc
  intersection.cc
  pixel.cc
  ray.cc
  render_settings.cc
  stop_watch.cc
  thread_pool.cc
  tile.cc
  point2f.cc
  point3f.cc
  vector2f.cc
  vector3f.cc
)
