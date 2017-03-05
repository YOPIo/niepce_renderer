#ifndef _VECTOR2_H__
#define _VECTOR2_H__

#include "../core/niepce.h"
#include "point2.h"

namespace niepce
{

template<typename T>
class Vector2
{
 public:
  Vector2(T v = 0.f) : x(v), y(v)
  {}
  Vector2(T xx, T yy) : x(xx), y(yy)
  {}
  explicit Vector2(const Point2<T>& p) : x(p.x), y(p.y)
  {
    Warningf(HasNaNs(), "Detected NaNs");
  }
  ~Vector2()
  {}

  Vector2(const Vector2& vec2) = default;
  Vector2(Vector2&& vec2)      = default;
  Vector2& operator = (const Vector2& vec2) = default;
  Vector2& operator = (Vector2&& vec2)      = default;

  auto operator == (const Vector2& v) const noexcept -> bool
  {
    return (x == v.x && y == v.y);
  }
  auto operator != (const Vector2& v) const noexcept -> bool
  {
    return (x != v.x || y != v.y);
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

  operator Point2<T>() const
  {
    return Point2<T>(x, y);
  }

  auto operator +  (const Vector2& v) const -> Vector2<T>
  {
    Warningf(v.HasNaNs(), "Detected NaNs");
    return Vector2<T>(x + v.x, y + v.y);
  }
  auto operator += (const Vector2& v) -> Vector2<T>&
  {
    Warningf(v.HasNaNs(), "Detected NaNs");
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator - (const Vector2& v) const -> Vector2<T>
  {
    Warningf(v.HasNaNs(), "Detected NaNs");
    return Vector2<T>(x - v.x, y - v.y);
  }
  auto operator -= (const Vector2& v) -> Vector2<T>&
  {
    Warningf(v.HasNaNs(), "Detected NaNs.");
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Vector2<T>
  {
    Warningf(IsNaNs(f), "Detected Nan.");
    return Vector2<T>(f * x, f * y);
  }

  template<typename U>
  auto operator *= (U f) -> Vector2<T>&
  {
    Warningf(IsNan(f), "Detected NaNs.");
    x *= f;
    y *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Vector2<T>
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    return Vector2<T>(x * inv, f * inv);
  }
  template<typename U>
  auto operator /= (U f) -> Vector2<T>&
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    x *= inv;
    y *= inv;
    return *this;
  }

  auto operator - () const noexcept -> Vector2<T>
  {
    return Vector2<T>(-x, -y);
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y);
  }

 public:
  T x, y;
};

/*
  Inline Global Functions
*/
template <typename T>
inline auto operator << (std::ostream& os, const Vector2<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <typename T, typename U>
inline auto operator * (U f, const Vector2<T>& v) -> Vector2<T>
{
  return v * f;
}

template <typename T>
inline auto Dot(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  Warningf(v1.HasNaNs() || v2.HasNaNs(), "Detected NaNs");
  return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline auto Cross(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  Warningf(v1.HasNaNs() || v2.HasNaNs(), "Detected NaNs");
  return v1.x * v2.y - v1.y * v2.x;
}

template <typename T>
inline auto Normalize(const Vector2<T>& v) -> Vector2<T>
{
  return v / v.Length();
}

template <typename T>
inline auto Abs(const Vector2<T>& v) -> Vector2<T>
{
  return Vector2<T>(std::abs(v.x), std::abs(v.y));
}

template <typename T>
inline auto Lerp(Float t, const Vector2<T>& v1, const Vector2<T>& v2) -> Vector2<T>
{
  return t * v1 + (1.f - t) * v2;
}

} // namespace niepce

#endif // _VECTOR2_H__
