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

  auto Max() const -> Point2<T>;
  auto Min() const -> Point2<T>;

  auto SetMax(const Point2<T>& bbox) -> void;
  auto SetMin(const Point2<T>& bbox) -> void;

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point2<T>;
  auto Diagonal() const -> Vector2<T>;
  auto Area() const -> T;

 private:
  Point2<T> min_, max_;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox2<T>& bbox) -> std::ostream&
{
  os << "[" << bbox.min_ << " - " << bbox.max_ << "]";
  return os;
}

/*
  Global functions
*/

template <typename T>
auto Union(const BoundingBox2<T>& bbox, const Point2<T>& p) -> BoundingBox2<T>;

template <typename T>
auto Union(const BoundingBox2<T>& bbox0, const BoundingBox2<T>& bbox1) -> BoundingBox2<T>;

}  // namespace niepce

#endif // _BOUNDING_BOX2_H_
