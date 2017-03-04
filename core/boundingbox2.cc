#include "boundingbox2.h"

namespace niepce
{

template <typename T>
BoundingBox2<T>::BoundingBox2() :
    min(Point2<T>::Max()), max(Point2<T>::Min())
{}
template <typename T>
BoundingBox2<T>::BoundingBox2(const Point2<T>& p1, const Point2<T>& p2) :
      min(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y)),
      max(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y))
{}

template <typename T>
virtual BoundingBox2<T>::~BoundingBox2();

template <typename T>
auto BoundingBox2<T>::operator == (const BoundingBox2<T>& bbox) -> bool
{
  return min == bbox.min && max == bbox.max;
}

template <typename T>
auto BoundingBox2<T>::operator != (const BoundingBox2<T>& bbox) -> bool
{
  return min != bbox.min || max != bbox.max;
}

template <typename T>
auto BoundingBox2<T>::operator [] (unsigned int idx) const -> Point2<T>
{
  Assertf(idx != 0 || idx != 1, "Out of bounds.");
  return idx == 0 ? min : max;
}

template <typename T>
auto BoundingBox2<T>::operator [] (unsigned int idx) -> Point2<T>
{
  Assertf(idx != 0 || idx != 1, "Out of bounds.");
  return idx == 0 ? min : max;
}

template <typename T>
auto BoundingBox2<T>::Corner(unsigned int idx) const -> Point2<T>
{
  Assertf(idx > 0 && idx < 2, "Out of bounds.");
  return Point2<T>((*this)[(idx & 1) ? 1 : 0].x,
                   (*this)[(idx & 2) ? 1 : 0].y);
}

template <typename T>
auto BoundingBox2<T>::Diagonal() const -> Vector2<T>
{
  return max - min;
}


template <typename T>
auto BoundingBox2<T>::Area() const -> T
{
  Vector2<T> d = Diagonal();
  return d.x * d.y;
}

template class BoundingBox2<int>;
template class BoundingBox2<Float>;

} // namespace niepce
