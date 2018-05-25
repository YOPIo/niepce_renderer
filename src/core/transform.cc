/*!
 * @file transform.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "transform.h"
#include "ray.h"
#include "point3f.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
/*!
 * @namespace niepce
 * @brief 
 * @details 
 */
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform (const Matrix4x4f& mat) : mat_ (mat), inv_ (Inverse (mat))
{}
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform (Float m00, Float m01, Float m02, Float m03,
                      Float m10, Float m11, Float m12, Float m13,
                      Float m20, Float m21, Float m22, Float m23,
                      Float m30, Float m31, Float m32, Float m33) :
  mat_ (m00, m01, m02, m03,
        m10, m11, m12, m13,
        m20, m21, m22, m23,
        m30, m31, m32, m33),
  inv_ (Inverse (mat_))
{}
/*
// ---------------------------------------------------------------------------
*/
Transform::Transform (const Matrix4x4f& mat, const Matrix4x4f& inv) :
  mat_ (mat),
  inv_ (inv)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::Matrix () const noexcept -> Matrix4x4f
{
  return mat_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::InverseMatrix () const noexcept -> Matrix4x4f
{
  return inv_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::operator () (unsigned int x, unsigned int y)
  const noexcept-> Float
{
  return mat_ (x, y);
}
/*
// ---------------------------------------------------------------------------
*/
auto Transform::At (unsigned int x, unsigned int y) const noexcept -> Float
{
  return mat_.At (x, y);
}
/*
// ---------------------------------------------------------------------------
// Transform operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Transform& lhs, const Transform& rhs) -> bool
{
  return (lhs.Matrix () == rhs.Matrix())
      && (lhs.InverseMatrix () == rhs.InverseMatrix ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator != (const Transform& lhs, const Transform& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, Float s) -> Transform
{
  return Transform (t.Matrix () * s);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float s, const Transform& t) -> Transform
{
  return Transform (s * t.Matrix ());
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Point3f& p) -> Point3f
{
  const Float x = p.X ();
  const Float y = p.Y ();
  const Float z = p.Z ();

  const Float xp = t (0, 0) * x + t (0, 1) * y + t (0, 2) * z + t (0, 3);
  const Float yp = t (1, 0) * x + t (1, 1) * y + t (1, 2) * z + t (1, 3);
  const Float zp = t (2, 0) * x + t (2, 1) * y + t (2, 2) * z + t (2, 3);
  const Float wp = t (3, 0) * x + t (3, 1) * y + t (3, 2) * z + t (3, 3);

  if (wp == 1) { return Point3f (xp, yp, zp); }
  return Point3f (xp, yp, zp) * (1.0 / wp);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Vector3f& v) -> Vector3f
{
  const Float x = v.X ();
  const Float y = v.Y ();
  const Float z = v.Z ();

  return Vector3f (t (0, 0) * x + t (0, 1) * y + t (0, 2) * z,
                   t (1, 0) * x + t (1, 1) * y + t (1, 2) * z,
                   t (2, 0) * x + t (2, 1) * y + t (2, 2) * z);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Transform& t, const Ray& ray) -> Ray
{
  return Ray (t * ray.Origin (), t * ray.Direction ());
}
/*
// ---------------------------------------------------------------------------
// Transform functions
// ---------------------------------------------------------------------------
*/
auto Transpose (const Transform& t) -> Transform
{
  return Transform (Transpose (t.Matrix ()), Transpose (t.InverseMatrix ()));
}
/*
// ---------------------------------------------------------------------------
*/
auto Inverse (const Transform& t) -> Transform
{
  return Transform (t.InverseMatrix (), t.Matrix ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Scale (Float x, Float y, Float z) -> Transform
{
  const Matrix4x4f mat (x, 0, 0, 0,
                        0, y, 0, 0,
                        0, 0, z, 0,
                        0, 0, 0, 1);
  const Matrix4x4f inv (1.0 / x, 0, 0, 0,
                        0, 1.0 / y, 0, 0,
                        0, 0, 1.0 / z, 0,
                        0, 0, 0, 1);
  return Transform (mat, inv);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
