#ifndef _SCREEN_H_
#define _SCREEN_H_

#include "../core/common.h"

namespace niepce
{

class ImageSensor
{
 public:
  ImageSensor();
  ~ImageSensor();

  ImageSensor(const ImageSensor& sensor) = default;
  ImageSensor(ImageSensor&& sensor)      = default;
  ImageSensor& operator = (const ImageSensor& sensor) = default;
  ImageSensor& operator = (ImageSensor&& sensor)      = default;

  auto Center() const -> glm::vec3;
  auto Width() const -> unsigned;
  auto Height() const -> unsigned;
  auto HorizontalAxis() const -> glm::vec3;
  auto VerticalAxis() const -> glm::vec3;

 private:
  glm::vec3 center_;
  SizeVec   size_vec_;
  Size      size_;
};

} // namespace niepce


#endif // _SENSOR_H_
