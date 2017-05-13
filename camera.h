#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "niepce.h"
#include "vector3.h"
#include "ray.h"

// ---------------------------------------------------------------------------
// Camera
// ---------------------------------------------------------------------------
class Camera
{
 public:
  Camera()
  {}
  Camera(const Vector3f& position_,
         const Vector3f& lookat_,
         const Vector3f& up_) :
      position(position_),
      direction( Normalize(lookat_ - position_) ),
      up( Normalize(up) )
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
  virtual ~Camera()
  {}

  Camera(const Camera& camera) = default;
  Camera(Camera&& camera)      = default;

  auto operator = (const Camera& camera) -> Camera& = default;
  auto operator = (Camera&& camera)      -> Camera& = default;

  /* Public methods */
  auto GenerateRay(unsigned int  x, unsigned int y,
                   unsigned int sx, unsigned int sy) -> Ray
  {
    const Float rate = 0.5;
    const Float r1 = static_cast<Float>(sx) * rate + rate / 2.0;
    const Float r2 = static_cast<Float>(sy) * rate + rate / 2.0;

    // Position on the sensor
    const Vector3f screen_position = sensor.center +
        sensor.x * ((r1 + x) / static_cast<Float>(kWidth)  - 0.5) +
        sensor.y * ((r2 + y) / static_cast<Float>(kHeight) - 0.5);

    const Vector3f ray_dir = Normalize(screen_position - position);
    return  Ray(position, ray_dir);
  }

 private:
  /* Private data structure */
  struct Sensor
  {
    Sensor() = default;
    Sensor(const Vector3f& x_,
           const Vector3f& y_,
           const Vector3f& center_) :
        x(x_), y(y_), center(center_)
    {}
    ~Sensor()
    {}

    Vector3f x;
    Vector3f y;
    Vector3f center;
  };
 private:
  /* Private data */
  Vector3f position;
  Vector3f direction;
  Vector3f up;
  Sensor   sensor;
};

#endif // _CAMERA_H_
