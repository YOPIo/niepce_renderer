#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "niepce.h"

namespace niepce
{

template<typename T>
class Vector3
{
 public:
  Vector3() : x(0), y(0), z(0)
  {}
  Vector3(Float xx, Float yy, Float zz) : x(xx), y(yy), z(zz)
  {
    DCHECK( !HasNan() );
  }
  explicit Vector3(const Point3<T>& p) : x(p.x), y(p.y), z(p.z)
  {
    DCHECK( !HasNan() );
  }
  virtual ~Vector3();

  Vector3(const Vector3& vec) = default;
  Vector3(Vector3&& vec)      = default;
  Vector3& operator = (const Vector3& vec) = default;
  Vector3& operator = (Vector3&& vec)      = default;

  auto operator == (const Vector3& v) const noexcept -> bool
  {
    return x == v.x && y == v.y && z == v.z;
  }
  auto operator != (const Vector3& v) const noexcept -> bool
  {
    return x != v.x || y != v.y || z != v.z;
  }

  auto operator [] (const unsigned int idx) const -> T
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (const unsigned int idx) -> T&
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  auto operator + (const Vector3& v) const -> Vector3
  {
    DCHECK( !v.HasNan() );
    return Vector3(x + v.x, y + v.y, z + v.z);
  }
  auto operator - (const Vector3& v) const -> Vector3
  {
    DCHECK( !v.HasNan() );
    return Vector3(x - v.x, y - v.y, z - v.z);
  }
  auto operator += (const Vector3& v) -> Vector3&
  {
    DCHECK( !v.HasNan() );
    x += v.x;
    y += v.y;
    z += v.z;
    return *this;
  }
  auto operator -= (const Vector3& v) -> Vector3&
  {
    DCHECK( !v.hasNan() );
    x -= v.x;
    y -= v.y;
    z -= v.z;
    return *this;
  }

  auto operator - () const noexcept -> Vector3
  {
    return Vector3(-x, -y, -z);
  }

  template<typename U>
  auto operator * (U f) -> Vector3
  {
    return Vector3(x * f, y * f, z * f);
  }
  template<typename U>
  auto operator / (U f) -> Vector3
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Vector3(x * inv, y * inv, z * inv);
  }
  template<typename U>
  auto operator *= (U f) -> Vector3&
  {
    DCHECK( !IsNan(f) );
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Vector3&
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
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
    return std::sqrt(LengthSquared());
  }
  auto HasNan() const -> bool
  {
    return niepce::IsNan(x) || niepce::IsNan(y) || niepce::IsNan(z);
  }

 public:
  T x, y, z;
};

template<typename T, typename U>
inline Vector3<T> operator * (U s, const Vector3<T>& v)
{
  return v * s;
}

template<typename T>
inline auto Dot(const Vector3<T>& v1, const Vector3<T> v2) -> T
{
  DCHECK( !v1.HanNan() && !v2.HasNan() );
  return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
}

template<typename T>
inline auto Cross(const Vector3<T>& v1, const Vector3<T> v2) -> Vector3<T>
{
  DCHECK( !v1.HasNan() && !v2.HasNan() );
  return Vector3<T>((v1.y * v2.z) - (v1.z * v2.y),
                    (v1.z * v2.x) - (v1.x * v2.z),
                    (v1.x * v2.y) - (v1.y * v2.x));
}

// TODO: Add nomal * vector cross
// TODO: Add vectro * normal cross

template<typename T>
inline auto Normalize(const Vector3<T>& v) -> Vector3<T>
{
  return v / v.Length();
}

template<typename T>
inline auto Abs(const Vector3<T>& v) -> Vector3<T>
{
  return Vector3<T>(std::abs(v.x), std::abs(v.y), std::abs(v.z));
}

template<typename T>
inline auto Distance(const Vector3<T>& v1, const Vector3<T>& v2) -> T
{
  return (v2 - v1).Length();
}

template<typename T>
inline auto CreateLocalCoordinateSystem(const Vector3<T>& v1, Vector3<T>* v2, Vector3<T>* v3) -> void
{
  if (std::abs(v1.x) > std::abs(v1.y))
  {
    *v2 = Normalize(Cross(Vector3<T>(0, 1, 0), v1));
  }else
  {
    *v2 = Normalize(Cross(Vector3<T>(1, 0, 0), v1));
  }
  *v3 = Cross(v1, *v2);
}

} // namespace niepce

#endif // _VECTOR3_H_
