#ifndef _VECTOR3_H_
#define _VECTOR3_H_

#include "niepce.h"

// ---------------------------------------------------------------------------
// Vector3 class
// ---------------------------------------------------------------------------
class Vector3f
{
 public:
  Vector3f() :
      x(0), y(0), z(0)
  {}
  Vector3f(const Float x_, const Float y_, const Float z_) :
      x(x_), y(y_), z(z_)
  {}
  virtual ~Vector3f()
  {}

  Vector3f(const Vector3f& vec) = default;
  Vector3f(Vector3f&& vec)      = default;

  /* Public operators */
  auto operator = (const Vector3f& vec) -> Vector3f& = default;
  auto operator = (Vector3f&& vec)      -> Vector3f& = default;
  inline auto operator + (const Vector3f &b) const -> Vector3f
  {
    return Vector3f(x + b.x, y + b.y, z + b.z);
  }
  inline auto operator - (const Vector3f &b) const -> Vector3f
  {
    return Vector3f(x - b.x, y - b.y, z - b.z);
  }
  inline auto operator * (Float f) const -> Vector3f
  {
    return Vector3f(x * f, y * f, z * f);
  }
  inline auto operator / (Float f) const -> Vector3f
  {
    return Vector3f(x / f, y / f, z / f);
  }
  /* Friend operator */
  friend inline auto operator * (Float f, const Vector3f &v)  -> Vector3f
  {
    return v * f;
  }

  /* Public methods */
  inline const Float LengthSquared() const
  {
    return x * x + y * y + z * z;
  }
  inline const Float Length() const
  {
    return sqrt(LengthSquared());
  }
  /* Friends methods */
  inline friend auto Normalize(const Vector3f &v) -> Vector3f
  {
    return v / v.Length();
  }
  inline friend auto Multiply(const Vector3f &v1, const Vector3f &v2) -> Vector3f
  {
    return Vector3f(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z);
  }
  inline friend auto Dot(const Vector3f &v1, const Vector3f &v2) -> Float
  {
    return v1.x * v2.x + v1.y * v2.y + v1.z * v2.z;
  }
  inline friend auto Cross(const Vector3f &v1, const Vector3f &v2) -> Vector3f
  {
    return Vector3f((v1.y * v2.z) - (v1.z * v2.y),
                    (v1.z * v2.x) - (v1.x * v2.z),
                    (v1.x * v2.y) - (v1.y * v2.x));
  }

  // ---------------------------------------------------------------------------
  // Vector3 public member data
  // ---------------------------------------------------------------------------
  Float x, y, z;
};

#endif // _VECTOR3_H_
