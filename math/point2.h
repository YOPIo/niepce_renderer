#ifndef _POINT2_H_
#define _POINT2_H_

#include "niepce.h"
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
    Warningf(HasNaN(), "Detected NaN");
  }
  virtual ~Point2();

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
    Assertf(0 <= idx && 2 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    return y;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(0 <= idx && 2 > idx, "Out of bounds.");
    if (idx == 0) { return x; }
    return y;
  }

  auto operator - (const Point2<T>& p) -> Vector2<T>
  {
    Warningf(p.HasNaN(), "Detected");
    return Vector2<T>(x - p.x, y - p.y);
  }
  auto operator -= (const Point2<T>& p) -> Vector2<T>&
  {
    Warningf(p.HasNaN(), "Detected");
    x -= p.x;
    y -= p.y;
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
  auto HasNaN() const -> bool
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

template <>
inline auto operator << (std::ostream& os, const Vector2<Float>& v) -> std::ostream&
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
inline auto Lerp(Float t, const Point2<T>& v1, const Point2<T>& v2)
{
  return t * v1 + (1.f - t) * v2;
}



}  // namespace niepce

#endif // _POINT2_H_
