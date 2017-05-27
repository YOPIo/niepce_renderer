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
  {}
  ~Vector2()
  {}

  Vector2(const Vector2& vec2) = default;
  Vector2(Vector2&& vec2)      = default;
  Vector2& operator = (const Vector2& vec2) = default;
  Vector2& operator = (Vector2&& vec2)      = default;


  // ---------------------------------------------------------------------------
  // Vector2 public operator
  // ---------------------------------------------------------------------------
  auto operator == (const Vector2& v) const noexcept -> bool
  {
    return (x == v.x && y == v.y);
  }
  auto operator != (const Vector2& v) const noexcept -> bool
  {
    return (x != v.x || y != v.y);
  }

  auto operator [] (std::size_t idx) const -> T
  {
#ifdef DEBUG
    try { return xy.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xy.at(idx);
#endif // DEBUG
  }
  auto operator [] (std::size_t idx) -> T&
  {
#ifdef DEBUG
    try { return xy.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xy.at(idx);
#endif // DEBUG
  }

  operator Point2<T>() const
  {
    return Point2<T>(x, y);
  }

  auto operator +  (const Vector2& v) const -> Vector2<T>
  {
    return Vector2<T>(x + v.x, y + v.y);
  }
  auto operator += (const Vector2& v) -> Vector2<T>&
  {
    x += v.x;
    y += v.y;
    return *this;
  }

  auto operator - (const Vector2& v) const -> Vector2<T>
  {
    return Vector2<T>(x - v.x, y - v.y);
  }
  auto operator -= (const Vector2& v) -> Vector2<T>&
  {
    x -= v.x;
    y -= v.y;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Vector2<T>
  {
    return Vector2<T>(f * x, f * y);
  }

  template<typename U>
  auto operator *= (U f) -> Vector2<T>&
  {
    x *= f;
    y *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Vector2<T>
  {
    Float inv = 1.0 / f;
    return Vector2<T>(x * inv, f * inv);
  }
  template<typename U>
  auto operator /= (U f) -> Vector2<T>&
  {
    Float inv = 1.0 / f;
    x *= inv;
    y *= inv;
    return *this;
  }

  auto operator - () const noexcept -> Vector2<T>
  {
    return Vector2<T>(-x, -y);
  }


  // ---------------------------------------------------------------------------
  // Vector2 public methods
  // ---------------------------------------------------------------------------
  auto LengthSquared() const -> Float
  {
    return x * x + y * y;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }


  // ---------------------------------------------------------------------------
  // Vector2 public constant values
  // ---------------------------------------------------------------------------
 public:
  static constexpr auto One() -> Vector2<T>
  {
    return Vector2<T>(1, 1);
  }
  static constexpr auto Zero() -> Vector2<T>
  {
    return Vector2<T>(0, 0);
  }
  static constexpr auto Max() -> Vector2<T>
  {
    return Vector2<T>(std::numeric_limits<T>::max(), std::numeric_limits<T>::max());
  }
  static constexpr auto Min() -> Vector2<T>
  {
    return Vector2<T>(std::numeric_limits<T>::min(), std::numeric_limits<T>::min());
  }
  static constexpr auto Inf() -> Vector2<T>
  {
    return Vector2<T>(std::numeric_limits<T>::infinity(),
                      std::numeric_limits<T>::infinity());
  }
  static constexpr auto NaN() -> Vector2<T>
  {
    return Vector2<T>(std::numeric_limits<T>::quiet_NaN(),
                      std::numeric_limits<T>::quiet_NaN());
  }
  static constexpr auto Eps() -> Vector2<T>
  {
    return Vector2<T>(std::numeric_limits<T>::epsilon(),
                      std::numeric_limits<T>::epsilon());
  }


  // ---------------------------------------------------------------------------
  // Vector2 private methods
  // ---------------------------------------------------------------------------
 private:
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y);
  }


  // ---------------------------------------------------------------------------
  // Vector2 public data
  // ---------------------------------------------------------------------------
 public:
  union
  {
    struct { T x, y; };
    std::array<T, 2> xy;
  };
};


// ---------------------------------------------------------------------------
// Inline Global Functions
// ---------------------------------------------------------------------------
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
inline auto operator * (const Vector2<T>& v1, const Vector2<T>& v2) -> Vector2<T>
{
  return Vector2<T>(v1.x * v2.x, v1.y * v2.y);
}

template <typename T>
inline auto Dot(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  // Check NaNs
  return v1.x * v2.x + v1.y * v2.y;
}

template <typename T>
inline auto Cross(const Vector2<T>& v1, const Vector2<T>& v2) -> T
{
  // Check NaNs
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

template <typename T>
inline auto Min(const Vector2<T>& v1, const Vector2<T>& v2) -> Vector2<T>
{
  return Vector2<T>(std::min(v1.x, v2.x),
                    std::min(v1.y, v2.y));
}

template <typename T>
inline auto Max(const Vector2<T>& v1, const Vector2<T>& v2) -> Vector2<T>
{
  return Vector2<T>(std::max(v1.x, v2.x),
                    std::max(v1.y, v2.y));
}

template <typename T>
inline auto MinComponentIndex(const Vector2<T>& v) -> int
{
  const T val = Min(v);
  if (val == v.x) { return 0; }
  return 1;
}

template <typename T>
inline auto MaxComponentIndex(const Vector2<T>& v) -> int
{
  const T val = Max(v);
  if (val == v.x) { return 0; }
  return 1;
}

} // namespace niepce

#endif // _VECTOR2_H__
