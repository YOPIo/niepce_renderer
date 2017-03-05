#ifndef _POINT_3_
#define _POINT_3_

#include "../core/niepce.h"
#include "vector3.h"

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
    Warningf(HasNaNs(), "Detected NaNs");
  }
  virtual ~Point3()
  {};

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
    Assertf(idx >= 2, "Out of bounds.");
    return *(&x + idx);
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(idx >= 2, "Out of bounds.");
    return *(&x + idx);
  }

  operator Vector3<T>() const
  {
    return Vector3<T>(x, y, z);
  }

  // Offset move
  auto operator + (const Vector3<T>& p) const -> Point3<T>
  {
    Warningf(p.HasNaNs(), "Detected NaNs.");
    return Point3<T>(x + p.x, y + p.y, z + p.z);
  }
  auto operator += (const Vector3<T>& p) const -> Point3<T>
  {
    Warningf(p.HasNaNs(), "Detected NaNs.");
    return Point3<T>(x + p.x, y + p.y, z + p.z);
  }

  auto operator * (T f) -> Point3<T>
  {
    Warningf(IsNaN(f), "Detected NaNs.");
    return Point3<T>(x * f, y * f, z * f);
  }
  auto operator *= (T f) -> Point3<T>&
  {
    Warningf(IsNaN(f), "Detected NaNs.");
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  auto operator / (T f) -> Point3<T>
  {
    Warningf(f == 0, "Detected NaNs.");
    Float inv = 1.f / f;
    return Point3<T>(x * inv, y * inv, z * inv);
  }
  auto operator /= (T f) -> Point3<T>&
  {
    Warningf(f == 0, "Detected NaNs.");
    Float inv = 1.f / f;
    x /= inv;
    y /= inv;
    z /= inv;
    return *this;
  }

  // Generate vector
  auto operator - (const Point3<T>& p) const -> Vector3<T>
  {
    Warningf(p.HasNaNs(), "Detected NaNs.");
    return Vector3<T>(x - p.x, y - p.y, z - p.z);
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y) || IsNaN(z);
  }

  static constexpr auto One() noexcept -> Point3<T>
  {
    return Point3<T>(1, 1, 1);
  }
  static constexpr auto Zero() noexcept -> Point3<T>
  {
    return Point3<T>(0, 0, 0);
  }
  static constexpr auto Max() noexcept -> Point3<T>
  {
    return Point3<T>(kMax, kMax, kMax);
  }
  static constexpr auto Min() noexcept -> Point3<T>
  {
    return Point3<T>(kMin, kMin, kMin);
  }
  static constexpr auto Infinity() noexcept -> Point3<T>
  {
    return Point3<T>(kInfinity, kInfinity, kInfinity);
  }

 public:
  T x, y, z;

 private:
  static constexpr T kInfinity = std::numeric_limits<T>::infinity();
  static constexpr T kMax      = std::numeric_limits<T>::max();
  static constexpr T kMin      = std::numeric_limits<T>::min();
};

/*
  Inline Global Functions
*/
template <typename T>
inline auto operator << (std::ostream& os, const Point3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return os;
}

template <typename T>
inline auto Distance(const Point3<T>& v1, const Point3<T>& v2) -> T
{
  return (v2 - v1).Length();
}

template <typename T>
inline auto DistanceSquared(const Point3<T>& v1, const Point3<T>& v2) -> T
{
  return (v2 - v1).LengthSquared();
}

template <typename T>
inline auto Lerp(Float t, const Point3<T>& v1, const Point3<T>& v2) -> Point3<T>
{
  return t * v1 + (1.f - t) * v2;
}

}  // namespace niepce

#endif // _POINT_3_
