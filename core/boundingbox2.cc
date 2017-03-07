#include "boundingbox2.h"

namespace niepce
{

template <typename T>
BoundingBox2<T>::BoundingBox2() :
    min_(Point2<T>::Max()), max_(Point2<T>::Min())
{}
template <typename T>
BoundingBox2<T>::BoundingBox2(const Point2<T>& p1, const Point2<T>& p2) :
      min_(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y)),
      max_(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y))
{}

template <typename T>
BoundingBox2<T>::~BoundingBox2()
{}

template <typename T>
auto BoundingBox2<T>::operator == (const BoundingBox2<T>& bbox) -> bool
{
  return min_ == bbox.min_ && max_ == bbox.max_;
}

template <typename T>
auto BoundingBox2<T>::operator != (const BoundingBox2<T>& bbox) -> bool
{
  return min_ != bbox.min_ || max_ != bbox.max_;
}

template <typename T>
auto BoundingBox2<T>::operator [] (unsigned int idx) const -> Point2<T>
{
  Assertf(idx != 0 || idx != 1, "Out of bounds.");
  return idx == 0 ? min_ : max_;
}

template <typename T>
auto BoundingBox2<T>::operator [] (unsigned int idx) -> Point2<T>
{
  Assertf(idx != 0 || idx != 1, "Out of bounds.");
  return idx == 0 ? min_ : max_;
}

template <typename T>
auto BoundingBox2<T>::Max() const -> Point2<T>
{
  return max_;
}

template <typename T>
auto BoundingBox2<T>::Min() const -> Point2<T>
{
  return min_;
}

template <typename T>
auto BoundingBox2<T>::SetMax(const Point2<T>& p) -> void
{
  max_ = p;
}

template <typename T>
auto BoundingBox2<T>::SetMin(const Point2<T>& p) -> void
{
  min_ = p;
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
  return max_ - min_;
}


template <typename T>
auto BoundingBox2<T>::Area() const -> T
{
  Vector2<T> d = Diagonal();
  return d.x * d.y;
}

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

template class BoundingBox2<int>;
template class BoundingBox2<Float>;

} // namespace niepce
