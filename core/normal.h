#ifndef _NORMAL_H_
#define _NORMAL_H_

#include "niepce.h"

namespace niepce
{

template<typename T>

class Normal
{
 public:
  Normal() : x(0), y(0), z(0)
  {};
  Normal(T xx, T yy, T zz) : x(xx), y(yy), z(zz)
  {}
  explicit Normal(const Vector3<T>& n) : x(n.x), y(n.y), z(n.z)
  {}
  virtual ~Normal()
  {}

  Normal(const Normal& n) = default;
  Normal(Normal&& n)      = default;
  Normal& operator = (const Normal& n) = default;  auto operator [] (unsigned int idx) const -> T&
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  Normal& operator = (Normal&& n)      = default;

  auto operator == (const Normal& n) const noexcept -> bool
  {
    return x == n.x && y == n.y && z == n.z;
  }
  auto operator != (const Normal& n) const noexcept -> bool
  {
    return x != n.x || y != n.y || z != n.z;
  }

  auto operator [] (unsigned int idx) const -> T
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }
  auto operator [] (unsigned int idx) -> T&
  {
    DCHECK(0 <= idx && idx < 3);
    if (idx == 0) { return x; }
    if (idx == 1) { return y; }
    return z;
  }

  auto operator + (const Normal& n) -> Normal
  {
    DCHECK( !n.HasNan() );
    return Normal(x + n.x, y + n.y, z + n.z);
  }
  auto operator - (const Normal& n) -> Normal
  {
    DCHEKC( !n.HasNan() );
    return Normal(x - n.x, y - n.y, z - n.z);
  }
  auto operator += (const Normal& n) -> Normal&
  {
    DCHECK( !n.HasNan() );
    x += n.x;
    y += n.y;
    z += n.z;
    return *this;
  }
  auto operator -= (const Normal& n) -> Normal&
  {
    DCHEKC( !n.HasNan() );
    x -= n.x;
    y -= n.y;
    z -= n.z;
    return *this;
  }

  auto operator - () const -> Normal
  {
    return Normal(-x, -y, -z);
  }

  template<typename U>
  auto operator * (U f) -> Normal
  {
    return Normal(x * f, y * f, z * f);
  }
  template<typename U>
  auto operator / (U f) -> Normal
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    return Normal(x * inv, y * inv, z * inv);
  }
  template<typename U>
  auto operator *= (U f) -> Normal&
  {
    x *= f;
    y *= f;
    z *= f;
    return *this;
  }
  template<typename U>
  auto operator /= (U f) -> Normal&
  {
    CHECK_NE(f, 0);
    Float inv = static_cast<Float>(1) / f;
    x *= inv;
    y *= inv;
    z *= inv;
    return *this;
  }

  auto LenghtSquared() const -> Float
  {
    return x * x + y * y + z * z;
  }
  auto Lenght() const -> Float
  {
    return std::sqrt(LenghtSquared());
  }
  auto HasNan() const -> bool
  {
    return IsNan(x) || IsNan(y) || IsNan(z);
  }

 public:
  T x, y, z;
};


} // namespace nipece

#endif // _NORMAL_H_
