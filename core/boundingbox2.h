#ifndef _BOUNDING_BOX2_H_
#define _BOUNDING_BOX2_H_

#include "niepce.h"
#include "../geometries/point2.h"

namespace niepce
{

template <typename T>
class BoundingBox2
{
 public:
  BoundingBox2();
  BoundingBox2(const Point2<T>& p1, const Point2<T>& p2);
  virtual ~BoundingBox2();

  BoundingBox2(const BoundingBox2& bbox3) = default;
  BoundingBox2(BoundingBox2&& bbox3)      = default;

  BoundingBox2& operator = (const BoundingBox2& bbox3) = default;
  BoundingBox2& operator = (BoundingBox2&& bbox3)      = default;

  auto operator == (const BoundingBox2<T>& bbox) -> bool;
  auto operator != (const BoundingBox2<T>& bbox) -> bool;

  auto operator [] (unsigned int idx) const -> Point2<T>;
  auto operator [] (unsigned int idx)       -> Point2<T>;

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point2<T>;
  auto Diagonal() const -> Vector2<T>;
  auto Area() const -> T;

 public:
  Point2<T> min, max;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox2<T>& bbox) -> std::ostream&
{
  os << "[" << bbox.min << " - " << bbox.max << "]";
  return os;
}

}  // namespace niepce

#endif // _BOUNDING_BOX2_H_
