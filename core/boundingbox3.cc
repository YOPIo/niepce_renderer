#include "boundingbox3.h"

namespace niepce
{

template <typename T>
BoundingBox3<T>::BoundingBox3() : min(Point3<T>::Max()), max(Point3<T>::Min())
{}

template <typename T>
BoundingBox3<T>::BoundingBox3(const Point3<T>& p1, const Point3<T>& p2) :
    min(std::fmin(p1.x, p2.x), std::fmin(p1.y, p2.y), std::fmin(p1.z, p2.z)),
    max(std::fmax(p1.x, p2.x), std::fmax(p1.y, p2.y), std::fmax(p1.z, p2.z))
{}

template <typename T>
BoundingBox3<T>::~BoundingBox3()
{}

template <typename T>
auto BoundingBox3<T>::operator == (const BoundingBox3<T>& bbox) -> bool
{
  return min == bbox.min && max == bbox.max;
}
template <typename T>
auto BoundingBox3<T>::operator != (const BoundingBox3<T>& bbox) -> bool
{
  return min != bbox.min || max != bbox.max;
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
  return max - min;
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
    Float near = (min[i] - ray.origin[i]) / inv_ray_direction;
    Float far  = (max[i] - ray.origin[i]) / inv_ray_direction;

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

} // namespace niepce
