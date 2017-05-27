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
  {}
  ~Vector3()
  {}
  Vector3(const Vector3& vec3) = default;
  Vector3(Vector3&& vec3)      = default;


  // ---------------------------------------------------------------------------
  // Vector3 public operators
  // ---------------------------------------------------------------------------
 public:
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

  auto operator [] (std::size_t idx) const -> T
  {
#ifdef DEBUG
    try { return xyz.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xyz[idx];
#endif // DEBUG
  }
  auto operator [] (std::size_t idx) -> T&
  {
#ifdef DEBUG
    try { return xyz.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xyz[idx];
#endif // DEBUG
  }

  operator Point3<T>() const
  {
    return Point3<T>(x, y, z);
  }
  operator Normal3<T> () const
  {
    return Normal3<T>(x, y, z);
  }

  auto operator + (const Vector3& v) const -> Vector3<T>
  {
    return Vector3<T>(x + v.x, y + v.y, z + v.z);
  }
  auto operator += (const Vector3& v) -> Vector3<T>&
  {
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }

  auto operator - (const Vector3& v) const -> Vector3<T>
  {
    return Vector3<T>(x - v.x, y - v.y, z - v.z);
  }
  auto operator -= (const Vector3& v) -> Vector3<T>&
  {
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Vector3<T>
  {
    return Vector3<T>(f * x, f * y, f * z);
  }
  template<typename U>
  auto operator *= (U f) -> Vector3<T>&
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Vector3<T>
  {
    Float inv = 1.0 / f;
    return Vector3<T>(x * inv, y * inv, z * inv);
  }
  template<typename U>
  auto operator /= (U f) -> Vector3<T>&
  {
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


  // ---------------------------------------------------------------------------
  // Vector3 public methods
  // ---------------------------------------------------------------------------
 public:
  auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }


  // ---------------------------------------------------------------------------
  // Vector3 public constant values
  // ---------------------------------------------------------------------------
  static constexpr auto One() -> Vector3<T>
  {
    return Vector3<T>(1, 1, 1);
  }
  static constexpr auto Zero() -> Vector3<T>
  {
    return Vector3<T>(0, 0, 0);
  }
  static constexpr auto Max() -> Vector3<T>
  {
    return Vector3<T>(std::numeric_limits<T>::max(),
                      std::numeric_limits<T>::max(),
                      std::numeric_limits<T>::max());
  }
  static constexpr auto Min() -> Vector3<T>
  {
    return Vector3<T>(std::numeric_limits<T>::min(),
                      std::numeric_limits<T>::min(),
                      std::numeric_limits<T>::min());
  }
  static constexpr auto Inf() -> Vector3<T>
  {
    return Vector3<T>(std::numeric_limits<T>::infinity(),
                      std::numeric_limits<T>::infinity(),
                      std::numeric_limits<T>::infinity());
  }
  static constexpr auto NaN() -> Vector3<T>
  {
    return Vector3<T>(std::numeric_limits<T>::quiet_NaN(),
                      std::numeric_limits<T>::quiet_NaN(),
                      std::numeric_limits<T>::quiet_NaN());
  }
  static constexpr auto Eps() -> Vector3<T>
  {
    return Vector3<T>(std::numeric_limits<T>::epsilon(),
                      std::numeric_limits<T>::epsilon(),
                      std::numeric_limits<T>::epsilon());
  }


  // ---------------------------------------------------------------------------
  // Vector3 private methods
  // ---------------------------------------------------------------------------
 private:
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y) || IsNaN(z);
  }


  // ---------------------------------------------------------------------------
  // Vector3 public data
  // ---------------------------------------------------------------------------
 public:
  union
  {
    struct { T x, y, z; };
    std::array<T, 3> xyz;
  };
};


// ---------------------------------------------------------------------------
// Inline Global Functions
// ---------------------------------------------------------------------------
template <typename T>
inline auto operator << (std::ostream& os, const Vector3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << ", " << v.z << "]";
  return os;
}

template <typename T, typename U>
inline auto operator * (U f, const Vector3<T>& v) -> Vector3<T>
{
  return v * f;
}

template <typename T>
inline auto Mult(const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  return Vector3<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
}

template <typename T>
inline auto Dot(const Vector3<T>& v1, const Vector3<T>& v2) -> T
{
  // Check NaNs
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template <typename T>
inline auto Dot(const Vector3<T>& v, const Point3<T>& p) -> T
{
  return p.x * v.x + p.y * v.y + p.z * v.z;
}

template <typename T>
inline auto Dot(const Point3<T>& p, const Vector3<T>& v) -> T
{
  return p.x * v.x + p.y * v.y + p.z * v.z;
}

template <typename T>
inline auto Cross(const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  // Check NaNs
  return Vector3<T>(v1.y * v2.z - v1.z * v2.y,
                    v1.z * v2.x - v1.x * v2.z,
                    v1.x * v2.y - v1.y * v2.x);
}

template <typename T>
inline auto Cross(const Vector3<T>& v, const Point3<T>& p) -> Vector3<T>
{
  // Check NaNs
  return Vector3<T>(v.y * p.z - v.z * p.y,
                    v.z * p.x - v.x * p.z,
                    v.x * p.y - v.y * p.x);
}

template <typename T>
inline auto Cross(const Point3<T>& p, const Vector3<T>& v) -> Vector3<T>
{
  // Check NaNs
  return Vector3<T>(v.y * p.z - v.z * p.y,
                    v.z * p.x - v.x * p.z,
                    v.x * p.y - v.y * p.x);
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

template <typename T>
inline auto Min(const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  return Vector3<T>(std::min(v1.x, v2.x),
                    std::min(v1.y, v2.y),
                    std::min(v1.z, v2.z));
}

template <typename T>
inline auto Max(const Vector3<T>& v1, const Vector3<T>& v2) -> Vector3<T>
{
  return Vector3<T>(std::max(v1.x, v2.x),
                    std::max(v1.y, v2.y),
                    std::max(v1.z, v2.z));
}

template <typename T>
inline auto MinComponentIndex(const Vector3<T>& p) -> int
{
  const T v = Min(p);
  if (v == p.x) { return 0; }
  if (v == p.y) { return 1; }
  return 2;
}

template <typename T>
inline auto MaxComponentIndex(const Vector3<T>& p) -> int
{
  const T v = Max(p);
  if (v == p.x) { return 0; }
  if (v == p.y) { return 1; }
  return 2;
}

template <typename T>
inline auto Permute(const Vector3<T>& p, int x, int y, int z) -> Vector3<T>
{
  return Vector3<T>(p[x], p[y], p[z]);
}

} // namespace niepce

#endif // _VECTOR4_H__
