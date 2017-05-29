#ifndef _POINT4_H__
#define _POINT4_H__

#include "../core/niepce.h"
#include "vector4.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Logger declaration
// ---------------------------------------------------------------------------
extern std::shared_ptr<spdlog::logger> console;

template<typename T>
class Point4
{
 public:
  Point4(T v = 0.f) : x(v), y(v), z(v), w(v)
  {}
  Point4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww)
  {}
  explicit Point4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)
  {}
  virtual ~Point4()
  {}

  Point4(const Point4& p4) = default;
  Point4(Point4&& p4)      = default;


  // ---------------------------------------------------------------------------
  // Point4 public operators
  // ---------------------------------------------------------------------------
 public:
  Point4& operator = (const Point4& p4) = default;
  Point4& operator = (Point4&& p4)      = default;

  auto operator == (const Point4& p) const noexcept -> bool
  {
    return (x == p.x && y == p.y && z == p.z && w == p.w);
  }
  auto operator != (const Point4& p) const noexcept -> bool
  {
    return (x != p.x || y != p.y || z != p.z || w != p.w);
  }

  auto operator [] (std::size_t idx) const -> T
  {
#ifdef Debug
    try { return xyzw.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xyzw[idx];
#endif // Debug
  }
  auto operator [] (std::size_t idx) -> T&
  {
#ifdef Debug
    try { return xyzw.at(idx); }
    catch (const std::out_of_range& e) { console->error(e.what()); }
#else
    return xyzw[idx];
#endif // Debug
  }

  operator Vector4<T>() const
  {
    return Vector4<T>(x, y, z, w);
  }

  auto operator + (const Point4& p) const -> Point4<T>
  {
    return Point4<T>(x + p.x, y + p.y, z + p.z, w + p.w);
  }
  auto operator += (const Point4& p) -> Point4<T>&
  {
    x += p.x;
    y += p.y;
    z += p.z;
    w += p.w;
    return *this;
  }

  auto operator - (const Point4& p) const -> Point4<T>
  {
    return Point4<T>(x - p.x, y - p.y, z - p.z, w - p.w);
  }
  auto operator -= (const Point4& p) -> Point4<T>&
  {
    x -= p.x;
    y -= p.y;
    z -= p.z;
    w -= p.w;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Point4<T>
  {
    return Point4<T>(f * x, f * y, f * z, f * w);
  }
  template<typename U>
  auto operator *= (U f) -> Point4<T>&
  {
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Point4<T>
  {
    Float inv = 1.0 / f;
    return Point4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  template<typename U>
  auto operator /= (U f) -> Point4<T>&
  {
    Float inv = 1.0 / f;
    x *= inv;
    y *= inv;
    z *= inv;
    w *= inv;
    return *this;
  }

  auto operator - () const -> Point4<T>
  {
    return Point4<T>(-x, -y, -z, -w);
  }

  auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z + w * w;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y) || IsNaN(z) || IsNaN(w);
  }


  // ---------------------------------------------------------------------------
  // Point4 public methods
  // ---------------------------------------------------------------------------
  static constexpr auto One() -> Point4<T>
  {
    return Point4<T>(1, 1, 1, 1);
  }
  static constexpr auto Zero() -> Point4<T>
  {
    return Point4<T>(0, 0, 0, 0);
  }
  static constexpr auto Max() -> Point4<T>
  {
    return Point4<T>(std::numeric_limits<T>::max(),
                     std::numeric_limits<T>::max(),
                     std::numeric_limits<T>::max(),
                     std::numeric_limits<T>::max());
  }
  static constexpr auto Min() -> Point4<T>
  {
    return Point4<T>(std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::min(),
                     std::numeric_limits<T>::min());
  }
  static constexpr auto Inf() -> Point4<T>
  {
    return Point4<T>(std::numeric_limits<T>::infinity(),
                     std::numeric_limits<T>::infinity(),
                     std::numeric_limits<T>::infinity(),
                     std::numeric_limits<T>::infinity());
  }
  static constexpr auto NaN() -> Point4<T>
  {
    return Point4<T>(std::numeric_limits<T>::quiet_NaN(),
                     std::numeric_limits<T>::quiet_NaN(),
                     std::numeric_limits<T>::quiet_NaN(),
                     std::numeric_limits<T>::quiet_NaN());
  }
  static constexpr auto Eps() -> Point4<T>
  {
    return Point4<T>(std::numeric_limits<T>::epsilon(),
                     std::numeric_limits<T>::epsilon(),
                     std::numeric_limits<T>::epsilon(),
                     std::numeric_limits<T>::epsilon());
  }


  // ---------------------------------------------------------------------------
  // Point4 public data
  // ---------------------------------------------------------------------------
 public:
  union
  {
    struct { T x, y, z, w; };
    std::array<T, 4> xyzw;
  };
};


// ---------------------------------------------------------------------------
// Inline Global Functions
// ---------------------------------------------------------------------------
template <typename T>
inline auto operator << (std::ostream& os, const Point4<T>& p) -> std::ostream&
{
  os << "[" << p.x << ", " << p.y << ", " << p.w << "]";
  return os;
}

template <typename T, typename U>
inline auto operator * (U f, const Point4<T>& p) -> Point4<T>
{
  return p * f;
}

template <typename T>
inline auto Dot(const Point4<T>& p1, const Point4<T>& p2) -> T = delete;

template <typename T>
inline auto Cross(const Point4<T>& p1, const Point4<T>& p2) -> Point4<T> = delete;

template <typename T>
inline auto Normalize(const Point4<T>& p) -> Point4<T>
{
  return p / p.Length();
}

template <typename T>
inline auto Abs(const Point4<T>& p) -> Point4<T>
{
  return Point4<T>(std::abs(p.x), std::abs(p.y), std::abs(p.z), std::abs(p.w));
}

template <typename T>
inline auto Lerp(Float t, const Point4<T>& p1, const Point4<T>& p2) -> Point4<T>
{
  return t * p1 + (1.f - t) * p2;
}

template <typename T>
inline auto Homogeneous(const Point4<T>& p) -> Point3<T>
{
  return Point3<T>(p.x, p.y, p.z) / p.w;
}

template <typename T>
inline auto Min(const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T>( std::min(p0.x, p1.x),
                    std::min(p0.y, p1.y),
                    std::min(p0.z, p1.z),
                    std::min(p0.w, p1.w));
}

template <typename T>
inline auto Max(const Point4<T>& p0, const Point4<T>& p1) -> Point4<T>
{
  return Point4<T>( std::max(p0.x, p1.x),
                    std::max(p0.y, p1.y),
                    std::max(p0.z, p1.z),
                    std::max(p0.w, p1.w));
}

} // namespace niepce

#endif // _POINT4_H__
