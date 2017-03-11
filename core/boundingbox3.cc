#include "boundingbox3.h"

namespace niepce
{

template <typename T>
BoundingBox3<T>::BoundingBox3() : min_(Point3<T>::Max()), max_(Point3<T>::Min())
{}

template <typename T>
BoundingBox3<T>::BoundingBox3(const Point3<T>& p1, const Point3<T>& p2) :
    min_(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)),
    max_(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z))
{}

template <typename T>
BoundingBox3<T>::~BoundingBox3()
{}

template <typename T>
BoundingBox3<T>::BoundingBox3(const std::initializer_list<Point3<T>>& list)
{
  Point3<T> max = Point3<T>::Min();
  Point3<T> min = Point3<T>::Max();
  for (auto& p : list)
  {
    min = niepce::Min(min, p);
    max = niepce::Max(max, p);
  }
  min_ = min;
  max_ = max;
}

template <typename T>
BoundingBox3<T>::BoundingBox3(std::initializer_list<Point3<T>>&& list)
{
  Point3<T> max = Point3<T>::Min();
  Point3<T> min = Point3<T>::Max();
  for (auto& p : list)
  {
    min = niepce::Min(min, p);
    max = niepce::Max(max, p);
  }
  min_ = min;
  max_ = max;
}

template <typename T>
auto BoundingBox3<T>::operator == (const BoundingBox3<T>& bbox) -> bool
{
  return min_ == bbox.min_ && max_ == bbox.max_;
}
template <typename T>
auto BoundingBox3<T>::operator != (const BoundingBox3<T>& bbox) -> bool
{
  return min_ != bbox.min_ || max_ != bbox.max_;
}

template <typename T>
auto BoundingBox3<T>::operator[](unsigned int idx) const -> Point3<T>
{
  Assertf(idx == 0 || idx == 1, "Out of bounds. [0, 1].");
  return idx == 0 ? min_ : max_;
}

template <typename T>
auto BoundingBox3<T>::operator[](unsigned int idx) -> Point3<T>&
{
  Assertf(idx == 0 || idx == 1, "Out of bounds. [0, 1].");
  return idx == 0 ? min_ : max_;
}

template <typename T>
auto BoundingBox3<T>::Min() const -> Point3<T>
{
  return min_;
}

template <typename T>
auto BoundingBox3<T>::Max() const -> Point3<T>
{
  return max_;
}

template<typename T>
auto BoundingBox3<T>::SetMin(const Point3<T> &p) -> void
{
  min_ = p;
}

template <typename T>
auto BoundingBox3<T>::SetMax(const Point3<T>& p) -> void
{
  max_ = p;
}

// Each corner is arranged in the order of Morton order.
template <typename T>
auto BoundingBox3<T>::Corner(unsigned int idx) const -> Point3<T>
{
  Assertf(idx > 0 && idx < 2, "Out of bounds.");
  return Point3<T>((*this)[(idx & 1) ? 1 : 0].x,
                   (*this)[(idx & 2) ? 1 : 0].y,
                   (*this)[(idx & 4) ? 1 : 0].z);
}

template <typename T>
auto BoundingBox3<T>::Diagonal() const -> Vector3<T>
{
  return max_ - min_;
}

template <typename T>
auto BoundingBox3<T>::SurfaceArea() const -> T
{
  Vector3<T> d = Diagonal();
  return 2 * (d.x * d.y + d.y * d.z + d.z * d.x);
}

template <typename T>
auto BoundingBox3<T>::Volume() const -> T
{
  Vector3<T> d = Diagonal();
  return d.x * d.y * d.z;
}
template <typename T>
auto BoundingBox3<T>::IsIntersect(const Ray& ray, Float* t_near, Float* t_far) const -> bool
{
  // fix: need to use ray.max value in _t1_.
  Float t0 = 0, t1 = kInfinity;
  for (int i = 0; i < 3; ++i)
  {
    // Calculate _t_near_ and _t_far_ at _i_th bounding box slab
    const Float inv_ray_direction = 1.f / ray.direction[i];
    Float near = (min_[i] - ray.origin[i]) / inv_ray_direction;
    Float far  = (max_[i] - ray.origin[i]) / inv_ray_direction;

    if (near > far) { std::swap(near, far); }

    // Update
    t0 = near > t0 ? near : t0;
    t1 = far  < t1 ? far  : t1;
    if (t0 > t1) { return false; }
  }
  if (t_near == nullptr) { *t_near = t0; }
  if (t_far  == nullptr) { *t_far  = t0; }
  return true;
}

template class BoundingBox3<int>;
template class BoundingBox3<Float>;

template <typename T>
auto Union(const BoundingBox3<T>& bbox, const Point3<T>& p) -> BoundingBox3<T>
{
  return BoundingBox3<T>( Point3<T>( Min(bbox.Min(), p) ),
                          Point3<T>( Max(bbox.Max(), p) ) );
}
template auto Union(const BBox3f& bbox, const Point3f& p) -> BBox3f;
template auto Union(const BBox3i& bbox, const Point3i& p) -> BBox3i;

template <typename T>
auto Union(const BoundingBox3<T>& bbox0, const BoundingBox3<T>& bbox1) -> BoundingBox3<T>
{
  return BoundingBox3<T>( Point3<T>( Min(bbox0.Min(), bbox1.Min() ) ),
                          Point3<T>( Max(bbox0.Max(), bbox1.Max() )) );
}

} // namespace niepce
