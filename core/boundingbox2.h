#ifndef _BOUNDING_BOX2_H_
#define _BOUNDING_BOX2_H_

#include "niepce.h"
#include "point2.h"

namespace niepce
{

template <typename T>
class BoundingBox2
{
 public:
  BoundingBox2() : min(Point2<T>::Max()), max(Point2<T>::Min())
  {}
  BoundingBox2(const Point2<T>& p1, const Point2<T>& p2) :
      min(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y)),
      max(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y))
  {}
  virtual ~BoundingBox2();
  BoundingBox2(const BoundingBox2& bbox3) = default;
  BoundingBox2(BoundingBox2&& bbox3)      = default;
  BoundingBox2& operator = (const BoundingBox2& bbox3) = default;
  BoundingBox2& operator = (BoundingBox2&& bbox3)      = default;

  auto operator == (const BoundingBox2<T>& bbox) -> bool
  {
    return min == bbox.min && max == bbox.max;
  }
  auto operator != (const BoundingBox2<T>& bbox) -> bool
  {
    return min != bbox.min || max != bbox.max;
  }

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point2<T>
  {
    Assertf(idx > 0 && idx < 2, "Out of bounds.");
    return Point2<T>((*this)[(idx & 1) ? 1 : 0].x,
                     (*this)[(idx & 2) ? 1 : 0].y);
  }
  auto Diagonal() const -> Vector3<T>
  {
    return max - min;
  }
  auto Area() const -> T
  {
    Vector3<T> d = Diagonal();
    return d.x * d.y;
  }

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
