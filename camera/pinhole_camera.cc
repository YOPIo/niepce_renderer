#include "pinhole_camera.h"

namespace niepce
{

PinholeCamera::PinholeCamera()
{}

PinholeCamera::PinholeCamera(const glm::vec3& position,
                             const glm::vec3& look_at,
                             const glm::vec3& up,
                             Float            distance,
                             Float            sensor_size) :
    position_(position),
    direction_(glm::normalize(look_at - position)),
    up_(up),
    distance_(distance),
    sensor_size_(sensor_size)
{}

PinholeCamera::~PinholeCamera()
{}

auto PinholeCamera::GenerateRay(unsigned width, unsigned height,
                                int x,          int y,
                                int sx,         int sy,
                                int num_subpixel) const -> Ray
{
  // TODO: append other sampling way
  Float sensor_width  = sensor_size_ * static_cast<Float>(width) / static_cast<Float>(height);
  Float sensor_height = sensor_size_;

  const glm::vec3 horizontal = glm::normalize( glm::cross(direction_, up_) ) * sensor_width;
  const glm::vec3 vertical   = glm::normalize( glm::cross(horizontal, direction_) ) * sensor_height;
  const glm::vec3 center     = position_ + direction_ * distance_;

  const Float rate = (1.0 / num_subpixel);
  const Float r1   = sx * rate + rate / 2.0;
  const Float r2   = sy * rate + rate / 2.0;

  // calculate position of image sensor
  const glm::vec3 position_on_sensor = center +
      horizontal * ((r1 + x) / width  - 0.5f) +
      vertical   * ((r2 + y) / height - 0.5f);

  // calculate ray direction form camera position
  const glm::vec3 ray_direction = glm::normalize(position_on_sensor - position_);
  const Ray ray(position_, ray_direction);
  return ray;
}

} // namespace niepce
