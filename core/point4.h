#ifndef _POINT4_H__
#define _POINT4_H__

#include "niepce.h"
#include "vector4.h"

namespace niepce
{

template<typename T>
class Point4
{
 public:
  Point4(T v = 0.f) : x(v), y(v), z(v), w(v)
  {}
  Point4(T xx, T yy, T zz, T ww) : x(xx), y(yy), z(zz), w(ww)
  {}
  explicit Point4(const Vector4<T>& v) : x(v.x), y(v.y), z(v.z), w(v.w)
  {
    Warningf(HasNaNs(), "Detected NaNs");
  }
  virtual ~Point4()
  {}
  Point4(const Point4& p4) = default;
  Point4(Point4&& p4)      = default;
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

  auto operator [] (unsigned int idx) const -> T
  {
    Assertf(idx >= 4, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    if (idx == 2) { return z; }
    return w;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(idx >= 4, "Out of bounds.");
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    if (idx == 2) { return z; }
    return w;
  }

  operator Vector4<T>() const
  {
    return Vector4<T>(x, y, z, w);
  }

  auto operator + (const Point4& p) const -> Point4<T>
  {
    Warningf(p.HasNan(), "Detected NaNs.");
    return Point4<T>(x + p.x, y + p.y, z + p.z, w + p.w);
  }
  auto operator += (const Point4& p) -> Point4<T>&
  {
    Warningf(p.HasNan(), "Detected NaNs.");
    x += p.x;
    y += p.y;
    z += p.z;
    w += p.w;
    return *this;
  }

  auto operator - (const Point4& p) const -> Point4<T>
  {
    Warningf(p.HasNan(), "Detected NaNs.");
    return Point4<T>(x - p.x, y - p.y, z - p.z, w - p.w);
  }
  auto operator -= (const Point4& p) -> Point4<T>&
  {
    Warningf(p.HasNan(), "Detected NaNs.");
    x -= p.x;
    y -= p.y;
    z -= p.z;
    w -= p.w;
    return *this;
  }

  template<typename U>
  auto operator * (U f) const -> Point4<T>
  {
    Warningf(IsNaNs(f), "Detected Nan.");
    return Point4<T>(f * x, f * y, f * z, f * w);
  }
  template<typename U>
  auto operator *= (U f) -> Point4<T>&
  {
    Warningf(IsNan(f), "Detected NaNs.");
    x *= f;
    y *= f;
    z *= f;
    w *= f;
    return *this;
  }

  template<typename U>
  auto operator / (U f) const -> Point4<T>
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.0 / f;
    return Point4<T>(x * inv, y * inv, z * inv, w * inv);
  }
  template<typename U>
  auto operator /= (U f) -> Point4<T>&
  {
    Warningf(f == 0, "Zero division.");
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

  static constexpr auto One() noexcept -> Point4<T>
  {
    return Point4<T>(1, 1, 1, 1);
  }
  static constexpr auto Zero() noexcept -> Point4<T>
  {
    return Point4<T>(0, 0, 0, 0);
  }
  static constexpr auto Max() noexcept -> Point4<T>
  {
    return Point4<T>(kMax, kMax, kMax, kMax);
  }
  static constexpr auto Min() noexcept -> Point4<T>
  {
    return Point4<T>(kMin, kMin, kMin, kMin);
  }
  static constexpr auto Infinity() noexcept -> Point4<T>
  {
    return Point4<T>(kInfinity, kInfinity, kInfinity, kInfinity);
  }

 public:
  T x, y, z, w;

 private:
  static constexpr T kInfinity = std::numeric_limits<T>::infinity();
  static constexpr T kMax      = std::numeric_limits<T>::max();
  static constexpr T kMin      = std::numeric_limits<T>::min();
};

/*
  Inline Global Functions
*/
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

} // namespace niepce

#endif // _POINT4_H__