#include "sphere.h"

namespace niepce
{

Sphere::Sphere(const glm::vec3& position, float radius) :
    position_(position),
    radius_(radius)
{}

auto Sphere::IsIntersect(const Ray &ray, HitRecord* hit_record) const -> bool
{

  const auto  v = position_ - ray.origin_;
  const float b = glm::dot(v, ray.direction_);
  const float c = b * b - glm::dot(v, v) + radius_ * radius_;

  if (c < 0.0)
  {
    return false;
  }

  const float sqrt_c = sqrt(c);
  const float t1 = (b - sqrt_c);
  const float t2 = (b + sqrt_c);

  if (t1 < kEps && t2 < kEps)
  {
    return false;
  }

  hit_record->distance_ = kEps < t1 ? t1 : t2;
  hit_record->position_ = ray.origin_ + hit_record->distance_ * ray.direction_;
  hit_record->normal_   = glm::normalize(hit_record->position_ - position_);
  return true;
}

} // namespace niepce
