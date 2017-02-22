#ifndef _POINT_3_
#define _POINT_3_

#include "niepce.h"

namespace niepce
{

template <typename T>
class Point3
{
 public:
  Point3(T v = 0.f) : x(v), y(v), z(v)
  {}
  Point3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
  {}
  explicit Point3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
  {
    Warningf(HasNaN(), "Detected NaN");
  }
  virtual ~Point3();

  Point3(const Point3& p) = default;
  Point3(Point3&& p)      = default;
  Point3& operator = (const Point3& p) = default;
  Point3& operator = (Point3&& p)      = default;

  auto operator == (const Point3<T>& p) -> bool
  {
    return (x == p.x && y == p.y && z == p.z);
  }
  auto operator != (const Point3<T>& p) -> bool
  {
    return (x != p.x || y != p.y || z != p.z);
  }

  auto operator [] (unsigned int idx) const -> T
  {
    Assertf(0 <= idx && 2 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(0 <= idx && 2 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  auto operator - (const Point3<T>& p) -> Vector3<T>
  {
    Warningf(v.HasNan(), "Detected NaN.");
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
  }
  auto operator -= (const Point3<T>& p) -> Vector3<T>&
  {
    Warningf(v.HasNan(), "Detected NaN.");
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }
  auto HasNaN() const -> bool
  {
    return IsNaN(x) || IsNaN(y) || IsNaN(z);
  }

 public:
  T x, y, z;
};

/*
  Inline Global Functions
*/
template <typename T>
inline auto operator << (std::ostream& os, const Vector3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <>
inline auto operator << (std::ostream& os, const Vector3<Float>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <typename T>
inline auto Distance(const Vector3<T>& v1, const Vector3<T>& v2) -> T
{
  return (v2 - v1).Length();
}

template <typename T>
inline auto DistanceSquared(const Vector3<T>& v1, const Vector3<T>& v2) -> T
{
  return (v2 - v1).LengthSquared();
}

template <typename T>
inline auto Lerp(Float t, const Vector3<T>& v1, const Vector3<T>& v2)
{
  return t * v1 + (1.f - t) * v2;
}

}  // niepce

#endif // _POINT_3_
