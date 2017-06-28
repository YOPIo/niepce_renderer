#include "camera.h"

namespace niepce
{

Camera::Camera ()
{}

Camera::Camera (const Point3f&  position,
                const Vector3f& direction,
                const Vector3f& up) :
      position_  (position),
      direction_ ( Normalize(direction) ),
      up_        ( Normalize(up) )
{
  // Distance, camera position to sensor
  const Float distance    = 45;
  const Float sensor_size = 30;

  const Vector3f sensor_x  = Normalize(Cross(direction, up_)) *
      sensor_size * (static_cast<Float>(kWidth)) / static_cast<Float>(kHeight);
  const Vector3f sensor_y  = Normalize(Cross(sensor_x, direction)) *
      sensor_size;
  const Vector3f center    = position_ + direction * distance;
  sensor = Sensor(sensor_x, sensor_y, center);
}

Camera::~Camera ()
{}

auto Camera::GenerateRay(unsigned int x, unsigned int y, unsigned int sx, unsigned int sy) -> Ray
{
  const Float rate = 0.5;
  const Float r1 = static_cast<Float>(sx) * rate + rate / 2.0;
  const Float r2 = static_cast<Float>(sy) * rate + rate / 2.0;

  // Position on the sensor
  const Vector3f screen_position = sensor.center +
      sensor.x * ((r1 + x) / static_cast<Float>(kWidth)  - 0.5) +
      sensor.y * ((r2 + y) / static_cast<Float>(kHeight) - 0.5);

  const Vector3f ray_dir = Normalize(screen_position - position_);
  return  Ray(position_, ray_dir);
}

}  // namespace niepce
