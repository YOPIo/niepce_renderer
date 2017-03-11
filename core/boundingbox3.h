#ifndef _BOUNDING_BOX3_H_
#define _BOUNDING_BOX3_H_

#include "niepce.h"
#include "../geometries/point3.h"
#include "../geometries/vector3.h"
#include "ray.h"

namespace niepce
{

template <typename T>
class BoundingBox3
{
 public:
  BoundingBox3();
  BoundingBox3(const Point3<T>& p1, const Point3<T>& p2);
  virtual ~BoundingBox3();

  BoundingBox3(const BoundingBox3<T>& bbox3) = default;
  BoundingBox3(BoundingBox3<T>&& bbox3)      = default;
  BoundingBox3& operator = (const BoundingBox3<T>& bbox3) = default;
  BoundingBox3& operator = (BoundingBox3<T>&& bbox3)      = default;

  BoundingBox3(const std::initializer_list<Point3<T>>& list);
  BoundingBox3(std::initializer_list<Point3<T>>&& list);

  auto operator == (const BoundingBox3<T>& bbox) -> bool;
  auto operator != (const BoundingBox3<T>& bbox) -> bool;

  auto operator [] (unsigned int idx) const -> Point3<T>;
  auto operator [] (unsigned int idx)       -> Point3<T>&;

  auto Min() const -> Point3<T>;
  auto Max() const -> Point3<T>;

  auto SetMin(const Point3<T>& p) -> void;
  auto SetMax(const Point3<T>& p) -> void;

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point3<T>;
  auto Diagonal() const -> Vector3<T>;
  auto SurfaceArea() const -> T;
  auto Volume() const -> T;
  auto IsIntersect(const Ray& ray, Float* t_near = nullptr, Float* t_far = nullptr) const -> bool;

 private:
  Point3<T> min_, max_;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox3<T>& bbox) -> std::ostream&
{
  os << "[" << bbox.min_ << " - " << bbox.max_ << "]";
  return os;
}

/*
  Global functions
*/
template <typename T>
auto Union(const BoundingBox3<T>& bbox, const Point3<T>& p) -> BoundingBox3<T>;

template <typename T>
auto Union(const BoundingBox3<T>& bbox0, const BoundingBox3<T>& bbox1) -> BoundingBox3<T>;

}  // namespace niepce

#endif // _BOUNDING_BOX3_H_
