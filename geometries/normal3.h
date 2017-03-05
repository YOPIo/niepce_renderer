#ifndef _NORMAL3_H_
#define _NORMAL3_H_

#include "../core/niepce.h"
#include "vector3.h"
#include "point3.h"

namespace niepce
{

template <typename T>
class Normal3
{
 public:
  Normal3(T v = 0.f) : x(v), y(v), z(v)
  {}
  Normal3(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
  {}
  explicit Normal3(const Vector3<T>& v) : x(v.x), y(v.y), z(v.z)
  {
    Warningf(HasNaNs(), "Detected NaN.");
  }
  virtual ~Normal3()
  {}
  Normal3(const Normal3& n) = default;
  Normal3(Normal3&& n)      = default;
  Normal3& operator = (const Normal3& n) = default;
  Normal3& operator = (Normal3&& n)      = default;

  auto operator == (const Normal3<T>& n) const noexcept -> bool
  {
    return (x == n.x && y == n.y && z == n.z);
  }
  auto operator != (const Normal3<T>& n) const noexcept -> bool
  {
    return (x == n.x && y == n.y && z == n.z);
  }

  auto operator [] (unsigned int idx) const -> T
  {
    Assertf(0 <= idx && 3 > idx, "Out of bounds.");
    return *(&x + idx);
  }
  auto operator [] (unsigned int idx) -> T&
  {
    Assertf(0 <= idx && 3 > idx, "Out of bounds.");
    return *(&x + idx);
  }

  operator Vector3<T>() const
  {
    return Vector3<T>(x, y, z);
  }

  // Basic operation
  auto operator + (const Normal3<T>& n) -> Normal3<T>
  {
    Warningf(n.HasNaNs(), "Detected NaN.");
    return Normal3<T>(x + n.x, y + n.y, z + n.z);
  }
  auto operator += (const Normal3<T>& n) -> Normal3<T>&
  {
    Warningf(n.HasNaNs(), "Detected NaN.");
    x += n.x;
    y += n.y;
    z += n.z;
    return *this;
  }

  auto operator - (const Normal3<T>& n) -> Normal3<T>
  {
    Warningf(n.HasNaNs(), "Detected NaN.");
    return Normal3<T>(x - n.x, y - n.y, z - n.z);
  }
  auto operator -= (const Normal3<T>& n) -> Normal3<T>&
  {
    Warningf(n.HasNaNs(), "Detected NaN.");
    x -= n.x;
    y -= n.y;
    z -= n.z;
    return *this;
  }

  auto operator * (T f) -> Normal3<T>
  {
    Warningf(IsNaN(f), "Detected NaN.");
    return Normal3<T>(x * f, y * f, z * f);
  }
  auto operator *= (T f) -> Normal3<T>&
  {
    Warningf(IsNaN(f), "Detected NaN.");
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }

  auto operator / (T f) -> Normal3<T>
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.f / f;
    return Normal3<T>(x * f, y * f, z * f);
  }
  auto operator /= (T f) -> Normal3<T>&
  {
    Warningf(f == 0, "Zero division.");
    Float inv = 1.f / f;
    x /= inv;
    y /= inv;
    z /= inv;
    return *this;
  }

  // Public methods
    auto LengthSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Length() const -> Float
  {
    return std::sqrt( LengthSquared() );
  }
  auto HasNaNs() const -> bool
  {
    return IsNaN(x) || IsNaN(y) || IsNaN(z);
  }

 public:
  T x, y, z;
};

/*
  Global inline functions
*/
template <typename T>
inline auto operator << (std::ostream& os, const Normal3<T>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <typename T>
inline auto operator * (T f, const Normal3<T>& n) -> Normal3<T>
{
  return n * f;
}

template <>
inline auto operator << (std::ostream& os, const Normal3<Float>& v) -> std::ostream&
{
  os << "[" << v.x << ", " << v.y << "]";
  return os;
}

template <typename T>
inline auto Dot(const Normal3<T>& n1, const Normal3<T>& n2) -> T
{
  Warningf(n1.HasNaN() || n2.HasNaN(), "Detected NaN.");
  return n1.x * n2.x + n1.y * n2.y + n1.z * n2.z;
}

template <typename T>
inline auto Dot(const Vector3<T>& v, const Normal3<T>& n) -> T
{
  Warningf(v.HasNaN() || n.HasNaN(), "Detected NaN.");
  return v.x * n.x + v.y * n.y + v.z * n.z;
}

template <typename T>
inline auto Dot(const Normal3<T>& n, const Vector3<T>& v) -> T
{
  Warningf(n.HasNaN() || v.HasNaN(), "Detected NaN.");
  return n.x * v.x + n.y * v.y + n.z * v.z;
}

template <typename T>
inline auto Cross(const Normal3<T>& n1, const Normal3<T>& n2) -> Normal3<T>
{
  Warningf(n1.HasNaN() || n2.HasNaN(), "Detected NaN.");
  return Normal3<T>(n1.y * n2.z - n1.z * n2.y,
                    n1.z * n2.x - n1.x * n2.z,
                    n1.x * n2.y - n1.y * n2.x);
}

template <typename T>
inline auto Cross(const Vector3<T>& v, const Normal3<T>& n) -> Vector3<T>
{
  Warningf(v.HasNaN() || n.HasNaN(), "Detected NaN.");
  return Vector3<T>(v.y * n.z - v.z * n.y,
                    v.z * n.x - v.x * n.z,
                    v.x * n.y - v.y * n.x);
}

template <typename T>
inline auto Cross(const Normal3<T>& n, const Vector3<T>& v) -> Vector3<T>
{
  Warningf(n.HasNaN() || v.HasNaN(), "Detected NaN.");
  return Vector3<T>(n.y * v.z - n.z * v.y,
                    n.z * v.x - n.x * v.z,
                    n.x * v.y - n.y * v.x);
}

template <typename T>
inline auto Normalize(const Normal3<T>& n) -> Normal3<T>
{
  return n / n.Length();
}

template <typename T>
inline auto Abs(const Normal3<T>& n) -> Normal3<T>
{
  return Normal3<T>(std::abs(n.x), std::abs(n.y), std::abs(n.z));
}

}  // namespace niepce

#endif // _NORMAL3_H_
