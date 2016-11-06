#include "image_sensor.h"

namespace niepce
{

ImageSensor::ImageSensor()
{}

ImageSensor::~ImageSensor()
{}

auto ImageSensor::Center() const -> glm::vec3
{
  return center_;
}

auto ImageSensor::HorizontalAxis() const -> glm::vec3
{
  return size_vec_.Horizontal();
}

auto ImageSensor::VerticalAxis() const -> glm::vec3
{
  return size_vec_.Vertical();
}

auto ImageSensor::Width() const -> unsigned
{
  return size_.Width();
}

auto ImageSensor::Height() const -> unsigned
{
  return size_.Height();
}

} // namespace niepce
