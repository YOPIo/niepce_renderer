#ifndef _BOUNDING_BOX2_H_
#define _BOUNDING_BOX2_H_

#include "../core/niepce.h"
#include "point2.h"

namespace niepce
{

template <typename T>
class BoundingBox2
{
 public:
  BoundingBox2() :
      min_(Point2<T>::Max()), max_(Point2<T>::Min())
  {}
  BoundingBox2(const Point2<T>& p1, const Point2<T>& p2) :
      min_(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y)),
      max_(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y))
  {}
  virtual ~BoundingBox2()
  {}

  BoundingBox2(const BoundingBox2& bbox3) = default;
  BoundingBox2(BoundingBox2&& bbox3)      = default;


  // ---------------------------------------------------------------------------
  // Boundingbox public operator
  // ---------------------------------------------------------------------------
 public:
  BoundingBox2& operator = (const BoundingBox2& bbox3) = default;
  BoundingBox2& operator = (BoundingBox2&& bbox3)      = default;

  auto operator == (const BoundingBox2<T>& bbox) -> bool
  {
    return min_ == bbox.min_ && max_ == bbox.max_;
  }
  auto operator != (const BoundingBox2<T>& bbox) -> bool
  {
    return !(min_ == bbox.min_ && max_ == bbox.max_);
  }

  auto operator [] (unsigned int idx) const -> Point2<T>
  {
    return idx == 0 ? min_ : max_;
  }
  auto operator [] (unsigned int idx) -> Point2<T>
  {
    return idx == 0 ? min_ : max_;
  }


  // ---------------------------------------------------------------------------
  // Boundingbox public methods
  // ---------------------------------------------------------------------------
 public:
  auto Max() const -> Point2<T>
  {
    return max_;
  }
  auto Min() const -> Point2<T>
  {
    return min_;
  }

  auto SetMax(const Point2<T>& max) -> void
  {
    max_ = max;
  }
  auto SetMin(const Point2<T>& min) -> void
  {
    min_ = min;
  }

  // Each corner is arranged in the order of Morton order.
  auto Corner(unsigned int idx) const -> Point2<T>
  {
    return Point2<T>((*this)[(idx & 1) ? 1 : 0].x,
                     (*this)[(idx & 2) ? 1 : 0].y);
  }
  auto Diagonal() const -> Vector2<T>
  {
    return max_ - min_;
  }
  auto SurfaceArea() const -> T
  {
    Vector2<T> d = Diagonal();
    return d.x * d.y;
  }


  // ---------------------------------------------------------------------------
  // Boundingbox private data
  // ---------------------------------------------------------------------------
 private:
  Point2<T> min_;
  Point2<T> max_;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox2<T>& bbox) -> std::ostream&
{
  os << "[" << bbox.min_ << " - " << bbox.max_ << "]";
  return os;
}

// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
template <typename T>
auto Union(const BoundingBox2<T>& bbox, const Point2<T>& p) -> BoundingBox2<T>
{
  return BoundingBox2<T>( Min(bbox.Min(), p), Min(bbox.Max(), p) );
}

template <typename T>
auto Union(const BoundingBox2<T>& bbox0, const BoundingBox2<T>& bbox1) -> BoundingBox2<T>
{
  return BoundingBox2<T>( Min(bbox0.Min(), bbox1.Min()),
                          Min(bbox0.Max(), bbox1.Max()) );
}

}  // namespace niepce

#endif // _BOUNDING_BOX2_H_
