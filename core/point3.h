#ifndef _POINT3_H_
#define _POINT3_H_

#include "niepce.h"

namespace niepce
{

template<typename T>
class Point3
{
 public:
  Point3() : x(0), y(0)
  {}
  Point3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
  {
    DCHECK( !HasNan() );
  }
  explicit Point3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
  {
    DCHECK( !HasNan() );
  }
  explicit Point3(const Normal3<T>& n) : x(n.x), y(n.y), z(n.z)
  {}
  template<typename U>
  explicit Point3(const Point3<U>& p) : x(p.x), y(p.y), z(p.z)
  {
    DCHECK( !HasNan() );
  }
  template<typename U>
  explicit Point3(const Vector3<U>& v) : x(v.x), y(v.y), z(v.z)
  {
    DCHECK( !HasNan() );
  }

  virtual ~Point3();

  Point3(const Point3& p) = default;
  Point3(Point3&& p)      = default;
  Point3& operator = (const Point3& p) = default;
  Point3& operator = (Point3&& p)      = default;

  auto operator == (const Point2<T>& p) -> bool
  {
    return x == p.x && y == p.y && z == p.z;
  }
  auto operator != (const Point2<T>& p) -> bool
  {
    return x != p.x || y != p.y || z != p.z;
  }

  auto operator [] (unsigned int idx) const -> T
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  template<typename U>
  explicit operator Vector3<U> () const
  {
    return Vector3<U>(x, y, z);
  }

  auto operator + (const Point3<T>& p) const -> Point3<T>
  {
    DCHECK( !p.HasNan() );
    return Point3<T>(x + p.x, y + p.y, z + p.z);
  }
  auto operator + (const Vector2<T>& v) const -> Point3<T>
  {
    DCHEKC( !v.HasNan() );
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }
  auto operator - (const Point3<T>& p) const -> Point3<T>
  {
    DCHECK( !p.HasNan() );
    return Point3<T>(x - p.x, y - p.y, y - p.z);
  }
  auto operator - (const Vector2<T>& v) const -> Point3<T>
  {
    DCHECK( !v.HasNan() );
    return Point3<T>(x + v.x, y + v.y, z + v.z);
  }

  auto operator += (const Point3<T>& p) -> Point3<T>&
  {
    DCHECK( !p.HasNan() );
    x += p.x;
    y += p.y;
    z += p.z;
    return *this;
  }
  auto operator += (const Vector2<T>& v) -> Point3<T>&
  {
    DCHECK( !v.HasNan() );
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator -= (const Point3<T>& p) -> Point3<T>&
  {
    DCHECK( !p.HasNan() );
    x -= p.x;
    y -= p.y;
    z -= p.z;
    return *this;
  }
  auto operator -= (const Vector2<T>& v) -> Point3<T>&
  {
    DCHECK( !v.HasNan() );
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Point3<T>
  {
    return Point3<T>(x * f, y * f, z * f);
  }
  template<typename U>
  auto operator / (U f) const -> Point3<T>
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Point3<T>(x * inv, y * inv, z * inv);
  }
  template<typename U>
  auto operator *= (U f) -> Point3<T>&
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Point3<T>&
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Point3<T>(x * inv, y * inv, z * inv);
  }

  auto operator - () const -> Point3<T>
  {
    return Point3<T>(-x, -y, -z);
  }

  auto HasNan() const -> bool
  {
    return niepce::IsNan(x) && niepce::IsNan(y) && niepce::IsNan(z);
  }
  auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Length() const -> Float
  {
    return std::sqrt( Length() );
  }

 public:
  T x, y, z;
};

template<typename T, typename U>
inline auto operator * (U f, Point3<T>& p) -> Point3<T>
{
  return p * f;
}

template<typename T>
inline auto Distance(const Point3<T>& p1, const Point3<T>& p2 ) -> Float
{
  return (p1 - p2).Lenght();
}

template<typename T>
inline auto Floor(const Point3<T>& p) -> Point3<T>
{
  return Point3<T>(std::floor(p.x), std::floor(p.y), std::floor(p.z));
}

template<typename T>
inline auto Ceil(const Point3<T>& p) -> Point3<T>
{
  return Point3<T>(std::ceil(p.x), std::ceil(p.y), std::ceil(p.z));
}

template<typename T>
inline auto Lerp(Float t, const Point2<T>& p1, const Point2<T>& p2) -> Point3<T>
{
  return (1 - t) * p1 + t * p2;
}

template<typename T>
inline auto Min(const Point3<T>& p1, const Point3<T>& p2) -> Point3<T>
{
  return Point3<T>(std::min(p1.x, p2.x), std::min(p1.y, p2.y), std::min(p1.z, p2.z)  );
}

template<typename T>
inline auto Max(const Point3<T>& p1, const Point3<T>& p2) -> Point3<T>
{
  return Point3<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y), std::max(p1.z, p2.z)  );
}

template<typename T>
inline auto Abs(const Point2<T>& p) -> Point3<T>
{
  return Point3<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z));
}

} // namespace niepce

#endif // _POINT3_H_
