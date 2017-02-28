#ifndef _VECTOR3_H__
#define _VECTOR3_H__

#include "../core/niepce.h"
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
    Warningf(HasNaNs(), "Detected NaNs");
  }
  virtual ~Vector3()
  {}
  Vector3(const Vector3& vec3) = default;
  Vector3(Vector3&& vec3)      = default;
  Vector3& operator = (const Vector3& vec3) = default;
  Vector3& operator = (Vector3&& vec3)      = default;

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
    Assertf(idx >= 3, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(idx >= 3, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  operator Point3<T>() const
  {
    return Point3<T>(x, y, z);
  }

  auto operator + (const Vector3& v) const -> Vector3<T>
  {
    Warningf(v.HasNan(), "Detected NaNs.");
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  auto operator += (const Vector3& v) -> Vector3<T>&
  {
    Warningf(v.HasNan(), "Detected NaNs.");
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator - (const Vector3& v) const -> Vector3<T>
  {
    Warningf(v.HasNan(), "Detected NaNs.");
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  auto operator -= (const Vector3& v) -> Vector3<T>&
  {
    Warningf(v.HasNan(), "Detected NaNs.");
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Vector3<T>
  {
    Warningf(IsNaNs(f), "Detected Nan.");
    return Vector3<T>(f * x, f * y, f * z);
  }
  template<typename U>
  auto operator *= (U f) -> Vector3<T>&
  {
    Warningf(IsNan(f), "Detected NaNs.");
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Vector3<T>
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
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

  auto operator - () const -> Vector3<T>
  {
    return Vector3<T>(-x, -y, -z);
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

  static constexpr auto One() noexcept -> Vector3<T>
  {
    return Vector3<T>(1, 1, 1);
  }
  static constexpr auto Zero() noexcept -> Vector3<T>
  {
    return Vector3<T>(0, 0, 0);
  }
  static constexpr auto Max() noexcept -> Vector3<T>
  {
    return Vector3<T>(kMax, kMax, kMax);
  }
  static constexpr auto Min() noexcept -> Vector3<T>
  {
    return Vector3<T>(kMin, kMin, kMin);
  }
  static constexpr auto Infinity() noexcept -> Vector3<T>
  {
    return Vector3<T>(kInfinity, kInfinity, kInfinity);
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
inline auto operator << (std::ostream& os, const Vector3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << ", " << v.z < "]";
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
  Warningf(v1.HasNaNs() || v2.HasNaNs(), "Detected NaNs");
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline auto Cross(const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  Warningf(v1.HasNaNs() || v2.HasNaNs(), "Detected NaNs.");
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
inline auto Lerp(Float t, const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  return t * v1 + (1.f - t) * v2;
}

} // namespace niepce

#endif // _VECTOR4_H__
