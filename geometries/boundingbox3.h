#ifndef _BOUNDING_BOX3_H_
#define _BOUNDING_BOX3_H_

#include "../core/niepce.h"
#include "../geometries/point3.h"
#include "../geometries/vector3.h"
#include "ray.h"

namespace niepce
{

template <typename T>
class BoundingBox3
{
 public:
  BoundingBox3 () :
      min_ ( Point3<T>::Max    () ),
      max_ ( Point3<T>::Lowest () )
  {}
  BoundingBox3 (const Point3<T>& p0, const Point3<T>& p1) :
      min_ ( std::min (p0.x, p1.x), std::min (p0.y, p1.y), std::min (p0.z, p1.z) ),
      max_ ( std::max (p0.x, p1.x), std::max (p0.y, p1.y), std::max (p0.z, p1.z) )
  {}
  BoundingBox3 (const std::initializer_list<Point3<T>>& list)
  {
    min_ = Point3<T>::Max    ();
    max_ = Point3<T>::Lowest ();
    for (auto& p : list)
    {
      min_ = niepce::Min (min_, p);
      max_ = niepce::Max (max_, p);
    }
  }
  BoundingBox3 (std::initializer_list<Point3<T>>&& list)
  {
    min_ = Point3<T>::Max    ();
    max_ = Point3<T>::Lowest ();
    for (auto& p : list)
    {
      min_ = niepce::Min (min_, p);
      max_ = niepce::Max (max_, p);
    }
  }

  virtual ~BoundingBox3()
  {}

  BoundingBox3 (const BoundingBox3<T>&  bbox3) = default;
  BoundingBox3 (      BoundingBox3<T>&& bbox3) = default;


  // ---------------------------------------------------------------------------
  // BoundingBox3 public operator
  // ---------------------------------------------------------------------------
 public:
  BoundingBox3& operator = (const BoundingBox3<T>&  bbox3) = default;
  BoundingBox3& operator = (      BoundingBox3<T>&& bbox3) = default;

  auto operator == (const BoundingBox3<T>& bbox) -> bool
  {
    return min_ == bbox.min_ && max_ == bbox.max_;
  }
  auto operator != (const BoundingBox3<T>& bbox) -> bool
  {
    return min_ != bbox.min_ || max_ != bbox.max_;
  }

  auto operator [] (unsigned int idx) const -> Point3<T>
  {
    return idx == 0 ? min_ : max_;
  }
  auto operator [] (unsigned int idx) -> Point3<T>&
  {
    return idx == 0 ? min_ : max_;
  }


  // ---------------------------------------------------------------------------
  // BoundingBox public methods
  // ---------------------------------------------------------------------------
  auto Min () const -> Point3<T>
  {
    return min_;
  }
  auto Max () const -> Point3<T>
  {
    return max_;
  }
  auto Centroid () const -> Point3<T>
  {
    return (max_ + min_) / 2.0;
  }

  auto SetMin (const Point3<T>& p) -> void
  {
    min_ = p;
  }
  auto SetMax (const Point3<T>& p) -> void
  {
    max_ = p;
  }

  // Each corner is arranged in the order of Morton order.
  auto Corner (unsigned int idx) const -> Point3<T>
  {
    // TODO: Range check [0, 2]
    return Point3<T>((*this)[(idx & 1) ? 1 : 0].x,
                     (*this)[(idx & 2) ? 1 : 0].y,
                     (*this)[(idx & 4) ? 1 : 0].z);
  }
  auto Diagonal () const -> Vector3<T>
  {
    return max_ - min_;
  }
  auto SurfaceArea () const -> T
  {
    Vector3<T> d = Diagonal();
    return 2 * (d.x * d.y + d.y * d.z + d.z * d.x);
  }
  auto Volume () const -> T
  {
    Vector3<T> d = Diagonal();
    return d.x * d.y * d.z;
  }
  auto MaxExtent () const -> int
  {
    const Vector3<T> v = Diagonal();
    if (v.x > v.y && v.x > v.z) { return 0; }
    if (v.y > v.z) { return 1; }
    return 2;
  }
  auto IsIntersect (const Ray& ray, Float* t_near = nullptr, Float* t_far = nullptr) const -> bool
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

 private:
  Point3<T> min_, max_;
};

template <typename T>
auto operator << (std::ostream& os, const BoundingBox3<T>& bounds) -> std::ostream&
{
  os << "[" << bounds.Min () << " - " << bounds.Max () << "]";
  return os;
}


// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
template <typename T>
auto Union (const BoundingBox3<T>& bounds, const Point3<T>& p) -> BoundingBox3<T>
{
  return BoundingBox3<T> ( Min (bounds.Min (), p),
                           Max (bounds.Max (), p) );
}

template <typename T>
auto Union (const BoundingBox3<T>& bounds0, const BoundingBox3<T>& bounds1) -> BoundingBox3<T>
{
  return BoundingBox3<T> ( Min (bounds0.Min (), bounds1.Min ()),
                           Max (bounds0.Max (), bounds1.Max ()) );
}

}  // namespace niepce

#endif // _BOUNDING_BOX3_H_
