#ifndef _PINHOLE_CAMERA_H_
#define _PINHOLE_CAMERA_H_

#include "../core/common.h"
#include "camera.h"

namespace niepce
{

class PinholeCamera : public Camera
{
 public:
  PinholeCamera();
  PinholeCamera(const glm::vec3& position,
                const glm::vec3& look_at,
                const glm::vec3& up,
                Float            distance,
                Float            sensor_size);
  ~PinholeCamera();

  PinholeCamera(const PinholeCamera& camera) = delete;
  PinholeCamera(PinholeCamera&& camera)      = delete;
  PinholeCamera& operator = (const PinholeCamera& camera) = delete;
  PinholeCamera& operator = (PinholeCamera&& camera)      = delete;

  auto GenerateRay(unsigned width, unsigned height,
                   int x,          int y,
                   int sx,         int sy,
                   int num_super_sample) const -> Ray;

 private:
  glm::vec3 position_;
  glm::vec3 direction_;
  glm::vec3 up_;
  Float     distance_; // distance between camera and image sensor
  Float     sensor_size_;
};

} // namespace niepce


#endif // _PINHOLE_CAMERA_H_
