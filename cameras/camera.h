#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../core/niepce.h"
#include "../geometries/ray.h"
#include "../geometries/vector3.h"

namespace niepce
{

class Camera
{
  /* Camera public constructors */
 public:
  Camera();
  Camera (const Point3f&  position_,
          const Vector3f& direction_,
          const Vector3f& up_);
  virtual ~Camera();

  Camera (const Camera& camera) = default;
  Camera (Camera&& camera)      = default;


  /* Camera public operators */
  auto operator = (const Camera& camera) -> Camera& = default;
  auto operator = (Camera&& camera)      -> Camera& = default;


  /* Camera public methods */
 public:
  auto GenerateRay(unsigned int  x, unsigned int y,
                   unsigned int sx, unsigned int sy) -> Ray;


  // ---------------------------------------------------------------------------
  // Camera private data
  // ---------------------------------------------------------------------------
 private:
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
  } sensor;

  Point3f  position_;
  Vector3f direction_;
  Vector3f up_;
};

}  // namespace niepce

#endif // _CAMERA_H_
