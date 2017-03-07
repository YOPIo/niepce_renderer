#ifndef _POINT2_H_
#define _POINT2_H_

#include "../core/niepce.h"
#include "vector2.h"

namespace niepce
{

template <typename T>
class Point2
{
 public:
  Point2(T v = 0.f) : x(v), y(v)
  {}
  Point2(T xx, T yy) : x(xx), y(yy)
  {}
  explicit Point2(const Vector2<T>& v) : x(v.x), y(v.y)
  {
    Warningf(!HasNaNs(), "Detected NaNs");
  }
  virtual ~Point2()
  {};

  Point2(const Point2& p) = default;
  Point2(Point2&& p)      = default;
  Point2& operator = (const Point2& p) = default;
  Point2& operator = (Point2&& p)      = default;

  auto operator == (const Point2<T>& p) -> bool
  {
    return (x == p.x && y == p.y);
  }
  auto operator != (const Point2<T>& p) -> bool
  {
    return (x != p.x || y != p.y);
  }

  auto operator [] (unsigned int idx) const -> T
  {
    Assertf(idx <= 1, "Out of range [0, 2].");
    return *(&x + idx);
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(idx <= 1, "Out of range [0, 2].");
    return *(&x + idx);
  }

  operator Vector2<T>() const
  {
    return Vector2<T>(x, y);
  }

  // Offset move
  auto operator + (const Vector2<T>& v) const -> Point2<T>
  {
    Warningf(!v.HasNaNs(), "Detected");
    return Point2<T>(x + v.x, y + v.y);
  }
  auto operator += (const Vector2<T>& v) -> Point2<T>&
  {
    Warningf(!v.HasNaNs(), "Detected");
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator * (T f) const -> Point2<T>
  {
    Warningf(!IsNaN(f), "Detected NaNs.");
    return Point2<T>(x * f, y * f);
  }
  auto operator *= (T f) -> Point2<T>&
  {
    Warningf(!IsNaN(f), "Detected NaNs.");
    x *= f;
    y *= f;
    return *this;
  }

  auto operator / (T f) const -> Point2<T>
  {
    Warningf(f != 0, "Zero division.");
    Float inv = 1.f / f;
    return Point2<T>(x * inv, y * inv);
  }
  auto operator /= (T f) -> Point2<T>&
  {
    Warningf(f != 0, "Zero division..");
    Float inv = 1.f / f;
    x /= inv;
    y /= inv;
    return *this;
  }

  // Generate vector
  auto operator - (const Point2<T>& p) const -> Vector2<T>
  {
    Warningf(!p.HasNaNs(), "Detected");
    return Vector2<T>(x - p.x, y - p.y);
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }

  /*
    Constexpr value
   */
  static constexpr auto One() -> Point2<T>
  {
    return Point2<T>(1, 1);
  }
  static constexpr auto Zero() -> Point2<T>
  {
    return Point2<T>(0, 0);
  }
  static constexpr auto Max() -> Point2<T>
  {
    return Point2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
  }
  static constexpr auto Min() -> Point2<T>
  {
    return Point2<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
  }
  static constexpr auto Inf() -> Point2<T>
  {
    return Point2<T>(std::numeric_limits<T>::infinity(),
                     std::numeric_limits<T>::infinity());
  }
  static constexpr auto NaN() -> Point2<T>
  {
    return Point2<T>(std::numeric_limits<T>::quiet_NaN(),
                     std::numeric_limits<T>::quiet_NaN());
  }
  static constexpr auto Eps() -> Point2<T>
  {
    return Point2<T>(std::numeric_limits<T>::epsilon(),
                     std::numeric_limits<T>::epsilon());
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
inline auto operator << (std::ostream& os, const Point2<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <typename T>
inline auto Distance(const Point2<T>& v1, const Point2<T>& v2) -> T
{
  return (v2 - v1).Length();
}

template <typename T>
inline auto DistanceSquared(const Point2<T>& v1, const Point2<T>& v2) -> T
{
  return (v2 - v1).LengthSquared();
}

template <typename T>
inline auto Lerp(Float t, const Point2<T>& v1, const Point2<T>& v2) -> Point2<T>
{
  return t * v1 + (1.f - t) * v2;
}

template <typename T>
inline auto Min(const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T>(std::min(p0.x, p1.x),
                   std::min(p0.y, p1.y));
}

template <typename T>
inline auto Max(const Point2<T>& p0, const Point2<T>& p1) -> Point2<T>
{
  return Point2<T>(std::max(p0.x, p1.x),
                   std::max(p0.y, p1.y));
}

}  // namespace niepce

#endif // _POINT2_H_
