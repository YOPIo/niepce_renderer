#ifndef _VECTOR2_H__
#define _VECTOR2_H__

#include "niepce.h"

namespace niepce
{

template<typename T>
class Vector2
{
 public:
  Vector2() : x(0), y(0)
  {};
  Vector2(T xx, T yy) : x(xx), y(yy)
  {}
  explicit Vector2(const Point2<T>& p) : x(p.x), y(p.y)
  {
    DCHECK( !HasNan() );
  }
  explicit Vector2(const Point3<T>& p) : x(p.x), y(p.y)
  {
    DCHECK( !HasNan() );
  }
  virtual ~Vector2()
  {};

  Vector2(const Vector2& vec2) = default;
  Vector2(Vector2&& vec2)      = default;
  Vector2& operator = (const Vector2& vec2) = default;
  Vector2& operator = (Vector2&& vec2)      = default;

  auto operator == (const Vector2& v) const noexcept -> bool
  {
    return x == v.x && y == v.y;
  }
  auto operator != (const Vector2& v) const noexcept -> bool
  {
    return x != v.x || y != v.y;
  }

  auto operator [] (unsigned int idx) const -> T
  {
    DCHECK(0 <= idx && idx < 2);
    if (idx == 0) { return x; }
    return y;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    DCHECK(0 <= idx && idx < 2);
    if (idx == 0) { return x; }
    return y;
  }

  auto operator +  (const Vector2& v) const -> Vector2
  {
    DCKECH( !v.HasNan() );
    return Vector2(x + v.x, y + v.y);
  }
  auto operator -  (const Vector2& v) const -> Vector2
  {
    DCHEKC( !v.HasNan() );
    return Vector2(x - v.x, y - v.y);
  }
  auto operator += (const Vector2& v) -> Vector2&
  {
    DCHECK( !v.HasNan() );
    x += v.x;
    y += v.y;
    return *this;
  }
  auto operator -= (const Vector2& v) -> Vector2&
  {
    DCHECK( !v.HasNan() );
    x -= v.x;
    y -= v.y;
    return *this;
  }

  auto operator - () const noexcept -> Vector2
  {
    return Vector2(-x, -y);
  }

  template<typename U>
  auto operator * (U f) const noexcept -> Vector2
  {
    return Vector2(x * f, y * f);
  }
  template<typename U>
  auto operator / (U f) const -> Vector2
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Vector2(x * inv, y * inv);
  }

  template<typename U>
  auto operator *= (U f) -> Vector2&
  {
    DCHECK( !IsNan(f) );
    x *= f;
    y *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Vector2&
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    x *= inv;
    y *= inv;
    return *this;
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }

  auto HasNan() const -> bool
  {
    return  niepce::IsNan(x) || niepce::IsNan(y);
  };

 public:
  T x, y;
};

template<typename T, typename U>
inline auto operator * (U f, const Vector2<T>& v) -> Vector2<T>
{
  return v * f;
}

template<typename T>
inline auto Dot(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  DCHECK( !v1.HasNan() && !v2.HasNan() );
  return v1.x * v2.x + v1.y * v2.y;
}

template<typename T>
inline auto Normalize(const Vector2<T>& v) -> Vector2<T>
{
  return v / v.Length();
}

template<typename T>
inline auto Abs(const Vector2<T>& v) -> Vector2<T>
{
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template<typename T>
inline auto Distance(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  return (v2 - v1).Length();
}

} // namespace niepce

#endif // _VECTOR2_H__
