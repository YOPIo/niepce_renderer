#ifndef _BOUNDING_BOX3_H_
#define _BOUNDING_BOX3_H_

#include "niepce.h"
#include "point3.h"
#include "vector3.h"
#include "ray.h"

// TODO: divide .h and .cc

namespace niepce
{

template <typename T>
class BoundingBox3
{
 public:
  BoundingBox3();
  BoundingBox3(const Point3<T>& p1, const Point3<T>& p2);
  virtual ~BoundingBox3();
  BoundingBox3(const BoundingBox3& bbox3) = default;
  BoundingBox3(BoundingBox3&& bbox3)      = default;
  BoundingBox3& operator = (const BoundingBox3& bbox3) = default;
  BoundingBox3& operator = (BoundingBox3&& bbox3)      = default;

  auto operator == (const BoundingBox3<T>& bbox) -> bool;
  auto operator != (const BoundingBox3<T>& bbox) -> bool;

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point3<T>;
  auto Diagonal() const -> Vector3<T>;
  auto SurfaceArea() const -> T;
  auto Volume() const -> T;
  auto IsIntersect(const Ray& ray, Float* t_near = nullptr, Float* t_far = nullptr) const -> bool;

 public:
  Point3<T> min, max;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox3<T>& bbox) -> std::ostream&
{
  os << "[" << bbox.min << " - " << bbox.max << "]";
  return os;
}

}  // namespace niepce

#endif // _BOUNDING_BOX3_H_
