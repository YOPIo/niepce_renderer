cmake_minimum_required (VERSION 3.0)

# Create static library
add_library (Core STATIC
  attributes.cc
  bounds2f.cc
  bounds3f.cc
  film.cc
  film_tile.cc
  intersection.cc
  pixel.cc
  ray.cc
  render_settings.cc
  stop_watch.cc
  material_attributes.cc
  thread_pool.cc
  memory.cc
  point2f.cc
  point3f.cc
  vector2f.cc
  vector3f.cc
  image.cc
  imageio.cc
  matrix4x4f.cc
  transform.cc
  singleton.cc
  shadow_ray.cc
  film.cc
)
