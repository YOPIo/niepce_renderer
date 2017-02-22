#ifndef _VECTOR3_H__
#define _VECTOR3_H__

#include "niepce.h"
#include "point2.h"
#include "point3.h"

namespace niepce
{

template<typename T>
class Vector3
{
 public:
  Vector3(T v = 0.f) : x(v), y(v), z(v)
  {}
  Vector3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
  {}
  explicit Vector3(const Point3<T>& p) : x(p.x), y(p.y), z(p.z)
  {
    Warningf(HasNaN(), "Detected NaN");
  }

  virtual ~Vector3()
  {}

  Vector3(const Vector3& vec2) = default;
  Vector3(Vector3&& vec2)      = default;
  Vector3& operator = (const Vector3& vec2) = default;
  Vector3& operator = (Vector3&& vec2)      = default;

  auto operator == (const Vector3& v) const noexcept -> bool
  {
    return (x == v.x && y == v.y && z == v.z);
  }
  auto operator != (const Vector3& v) const noexcept -> bool
  {
    return (x != v.x || y != v.y || z != v.z);
  }

  auto operator [] (unsigned int idx) const -> T
  {
    Assertf(0 <= idx && 3 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(0 <= idx && 3 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  auto operator + (const Vector3& v) const -> Vector3<T>
  {
    Warningf(v.HasNan(), "Detected NaN.");
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  auto operator - (const Vector3& v) const -> Vector3<T>
  {
    Warningf(v.HasNan(), "Detected NaN.");
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }

  auto operator += (const Vector3& v) -> Vector3<T>&
  {
    Warningf(v.HasNan(), "Detected NaN.");
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  auto operator -= (const Vector3& v) -> Vector3<T>&
  {
    Warningf(v.HasNan(), "Detected NaN.");
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  auto operator - () const noexcept -> Vector3<T>
  {
    return Vector3<T>(-x, -y, -z);
  }

  template<typename U>
  auto operator * (U f) const noexcept -> Vector3<t>
  {
    Warningf(IsNaN(f), "Detected Nan.");
    return Vector3<T>(f * x, f * y, f * z);
  }
  template<typename U>
  auto operator / (U f) const -> Vector3<T>
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    return Vector3<T>(x * inv, f * inv, f * inv);
  }

  template<typename U>
  auto operator *= (U f) -> Vector3<T>&
  {
    Warningf(IsNan(f), "Detected NaN.");
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Vector3<T>&
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    x *= inv;
    y *= inv;
    z *= inv;
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
  auto Max() const -> T
  {
    return std::fmax(x, std::fmax(y, z));
  }
  auto Min() const -> T
  {
    return std::fmin(x, std::fmin(y, z));
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

template <typename T, typename U>
inline auto operator * (U f, const Vector3<T>& v) -> Vector3<T>
{
  return v * f;
}

template <typename T>
inline auto Dot(const Vector3<T>& v1, const Vector3<T>& v2) -> T
{
  Warningf(v1.HasNaN() || v2.HasNaN(), "Detected NaN");
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline auto Cross(const Vector3<T>& v1, const Vector3<T>7 v2) -> Vector3<T>
{
  Warningf(v1.HasNaN() || v2.HasNaN(), "Detected NaN.");
  return Vector3<T>(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}

template <typename T>
inline auto Normalize(const Vector3<T>& v) -> Vector3<T>
{
  return v / v.Length();
}

template <typename T>
inline auto Abs(const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
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

} // namespace niepce

#endif // _VECTOR2_H__
