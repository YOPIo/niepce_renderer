#ifndef _CAMERA_H_
#define _CAMERA_H_

#include "../core/common.h"
#include "image_sensor.h"

namespace niepce
{

class Camera
{
 protected:
  Camera();

 public:
  virtual ~Camera();

  Camera(const Camera& camera) = delete;
  Camera(Camera&& camera)      = delete;
  Camera& operator = (const Camera& camera) = delete;
  Camera& operator = (Camera&& camera)      = delete;

  virtual auto GenerateRay(unsigned width, unsigned height,
                           int      x,     int      y,
                           int      sx,    int      sy,
                           int num_sample) const -> Ray = 0;
};


} // namespace niepce

#endif // _CAMERA_H_
