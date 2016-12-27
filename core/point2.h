#ifndef _POINT2_H_
#define _POINT2_H_

#include "niepce.h"

namespace niepce
{

template<typename T>
class Point2
{
 public:
  Point2() : x(0), y(0)
  {}
  Point2(T xx, T yy) : x(xx), y(yy)
  {
    DCHECK( !HasNan() );
  }
  explicit Point2(const Point3<T>& p) : x(p.x), y(p.y)
  {
    DCHECK( !HasNan() );
  }
  explicit Point2(const Vector3<T>& v) : x(v.x), y(v.y)
  {
    DCHECK( !HasNan() );
  }
  template<typename U>
  explicit Point2(const Point2<U>& p) : x(static_cast<T>(p.x)), y(static_cast<T>(p.y))
  {
    DCHEKC( !HasNan() );
  }
  template<typename U>
  explicit Point2(const Vector2<U>& p) : x(static_cast<T>(p.x)), y(static_cast<T>(p.y))
  {
    DCHEKC( !HasNan() );
  }
  virtual ~Point2()
  {}

  Point2(const Point2& p) = default;
  Point2(Point2&& p)      = default;
  Point2& operator = (const Point2& p) = default;
  Point2& operator = (Point2&& p)      = default;

  auto operator == (const Point2<T>& p) const -> bool
  {
    return x == p.x && y == p.y;
  }
  auto operator != (const Point2<T>& p) const -> bool
  {
    return x != p.x || y != p.y;
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

  template<typename U>
  explicit operator Vector2<U> () const
  {
    return Vector2<U>(x, y);
  }

  auto operator + (const Point2<T>& p) const -> Point2<T>
  {
    DCHECK( !p.HasNan() );
    return Point2<T>(x + p.x, y + p.y);
  }
  auto operator + (const Vector2<T>& v) const -> Point2<T>
  {
    DCHEKC( !v.HasNan() );
    return Point2<T>(x + v.x, y + v.y);
  }
  auto operator - (const Point2<T>& p) const -> Point2<T>
  {
    DCHECK( !p.HasNan() );
    return Point2<T>(x - p.x, y - p.y);
  }
  auto operator - (const Vector2<T>& v) const -> Point2<T>
  {
    DCHECK( !v.HasNan() );
    return Point2<T>(x + v.x, y + v.y);
  }

  auto operator += (const Point2<T>& p) -> Point2<T>&
  {
    DCHECK( !p.HasNan() );
    x += p.x;
    y += p.y;
    return *this;
  }
  auto operator += (const Vector2<T>& v) -> Point2<T>&
  {
    DCHECK( !v.HasNan() );
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator -= (const Point2<T>& p) -> Point2<T>&
  {
    DCHECK( !p.HasNan() );
    x -= p.x;
    y -= p.y;
    return *this;
  }
  auto operator -= (const Vector2<T>& v) -> Point2<T>&
  {
    DCHECK( !v.HasNan() );
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Point2<T>
  {
    return Point2<T>(x * f, y * f);
  }
  template<typename U>
  auto operator / (U f) const -> Point2<T>
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Point2<T>(x * inv, y * inv);
  }
  template<typename U>
  auto operator *= (U f) -> Point2<T>&
  {
    x *= f;
    y *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Point2<T>&
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Point2<T>(x * inv, y * inv);
  }

  auto operator - () const -> Point2<T>
  {
    return Point3<T>(-x, -y);
  }

  auto HasNan() const -> bool
  {
    return niepce::IsNan(x) && niepce::IsNan(y);
  }
  auto LengthSquared() const -> Float
  {
    return x * x + y * y;
  }
  auto Length() const -> Float
  {
    return std::sqrt( Length() );
  }

 public:
  T x, y;
};

template<typename T, typename U>
inline auto operator * (U f, Point2<T>& p) -> Point2<T>
{
  return p * f;
}

template<typename T>
inline auto Distance(const Point2<T>& p1, const Point2<T>& p2) -> Float
{
  return (p1 - p2).Length();
}

template<typename T>
inline auto Floor(const Point2<T>& p) -> Point2<T>
{
  return Point2<T>(std::floor(p.x), std::floor(p.y));
}

template<typename T>
inline auto Ceil(const Point2<T>& p) -> Point2<T>
{
  return Point2<T>(std::ceil(p.x), std::ceil(p.y));
}

template<typename T>
inline auto Lerp(Float t, const Point2<T>& p1, const Point2<T>& p2) -> Point2<T>
{
  return (1 - t) * p1 + t * p2;
}

template<typename T>
inline auto Min(const Point2<T>& p1, const Point2<T>& p2) -> Point2<T>
{
  return Point2<T>(std::min(p1.x, p2.x), std::min(p2.y, p2.y));
}

template<typename T>
inline auto Max(const Point2<T>& p1, const Point2<T>& p2) -> Point2<T>
{
  return Point2<T>(std::max(p1.x, p2.x), std::max(p1.y, p2.y));
}

template<typename T>
inline auto Abs(const Point2<T>& p) -> Point2<T>
{
  return Point2<T>(std::abs(p.x), std::abs(p.y));
}

} // namespace niepce

#endif // _POINT2_H_
