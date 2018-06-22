/*!
 * @file bounds3f.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bounds3f.h"
#include "ray.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Bounds3f::Bounds3f (const Point3f& p1, const Point3f& p2)
{
  const Float minx = std::fmin (p1.X (), p2.X ());
  const Float miny = std::fmin (p1.Y (), p2.Y ());
  const Float minz = std::fmin (p1.Z (), p2.Z ());
  const Float maxx = std::fmax (p1.X (), p2.X ());
  const Float maxy = std::fmax (p1.Y (), p2.Y ());
  const Float maxz = std::fmax (p1.Z (), p2.Z ());

  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Center () const noexcept -> Point3f
{
  return Point3f ((min_.X () + max_.X ()) * 0.5,
                  (min_.Y () + max_.Y ()) * 0.5,
                  (min_.Z () + max_.Z ()) * 0.5);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Diagonal () const noexcept -> Vector3f
{
  return max_ - min_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Min () const noexcept -> Point3f
{
  return min_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Max () const noexcept -> Point3f
{
  return max_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SetMin (const Point3f& p) noexcept -> void
{
  min_ = p;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SetMax (const Point3f& p) noexcept -> void
{
  max_ = p;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::SurfaceArea () const noexcept -> Float
{
  const Vector3f d = Diagonal ();
  return 2.0 * d.X () * d.Y ()
         + 2.0 * d.Y () * d.Z ()
         + 2.0 * d.Z () * d.X ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Merge (const Bounds3f& bounds) -> void
{
  const Point3f& min = bounds.Min ();
  const Point3f& max = bounds.Max ();

  const Float minx = std::fmin (min_.X (), min.X ());
  const Float miny = std::fmin (min_.Y (), min.Y ());
  const Float minz = std::fmin (min_.Z (), min.Z ());
  const Float maxx = std::fmax (max_.X (), max.X ());
  const Float maxy = std::fmax (max_.Y (), max.Y ());
  const Float maxz = std::fmax (max_.Z (), max.Z ());

  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::Merge (const Point3f& p) -> void
{
  const Float minx = std::fmin (min_.X (), p.X ());
  const Float miny = std::fmin (min_.Y (), p.Y ());
  const Float minz = std::fmin (min_.Z (), p.Z ());
  const Float maxx = std::fmax (max_.X (), p.X ());
  const Float maxy = std::fmax (max_.Y (), p.Y ());
  const Float maxz = std::fmax (max_.Z (), p.Z ());
  min_ = Point3f (minx, miny, minz);
  max_ = Point3f (maxx, maxy, maxz);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::ToString () const noexcept -> std::string
{
  std::string res ("min : " + min_.ToString() + "\nmax : " + max_.ToString ());
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bounds3f::IsIntersect (const Ray& ray) const noexcept -> bool
{
  Float t_max = kInfinity;
  Float t_min = -kInfinity;

  for (int i = 0; i < 3; ++i)
  {
    const Float t1 = (min_[i] - ray.Origin ()[i]) / ray.Direction ()[i];
    const Float t2 = (max_[i] - ray.Origin ()[i]) / ray.Direction ()[i];
    const Float t_near = std::fmin (t1, t2);
    const Float t_far  = std::fmax (t1, t2);
    t_max = std::fmin (t_max, t_far);
    t_min = std::fmax (t_min, t_near);
    if (t_min > t_max) { return false; }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto Union (const Bounds3f& lhs, const Bounds3f& rhs) -> Bounds3f
{
  const Point3f lmin = lhs.Min ();
  const Point3f lmax = lhs.Max ();
  const Point3f rmin = rhs.Min ();
  const Point3f rmax = rhs.Max ();

  const Float min_x = std::fmin (lmin.X (), rmin.X ());
  const Float min_y = std::fmin (lmin.Y (), rmin.Y ());
  const Float min_z = std::fmin (lmin.Z (), rmin.Z ());
  const Float max_x = std::fmax (lmax.X (), rmax.X ());
  const Float max_y = std::fmax (lmax.Y (), rmax.Y ());
  const Float max_z = std::fmax (lmax.Z (), rmax.Z ());

  return Bounds3f (Point3f (min_x, min_y, min_z),
                   Point3f (max_x, max_y, max_z));
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
