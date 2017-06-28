#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../core/niepce.h"
#include "../geometries/matrix4x4.h"
#include "../geometries/point3.h"
#include "../geometries/vector3.h"
#include "../geometries/normal3.h"
#include "../geometries/ray.h"
#include "../geometries/boundingbox3.h"

namespace niepce
{

class Transform
{
  /* Transform public constructors */
 public:
  Transform ();
  Transform (Float m00, Float m01, Float m02, Float m03,
             Float m10, Float m11, Float m12, Float m13,
             Float m20, Float m21, Float m22, Float m23,
             Float m30, Float m31, Float m32, Float m33);
  Transform (const Matrix4x4& m);
  virtual ~Transform ();

  Transform (const Transform&  t) = default;
  Transform (      Transform&& t) = default;


  /* Transform public operators */
 public:
  auto operator = (const Transform&  t) -> Transform& = default;
  auto operator = (      Transform&& t) -> Transform& = default;

  auto operator == (const Transform& t) const -> bool;
  auto operator != (const Transform& t) const -> bool;

  // This method does not throw a exception
  auto operator () (unsigned int row, unsigned int col) const -> Float;
  auto operator () (unsigned int row, unsigned int col)       -> Float;

  auto operator * (const Point3f&  p)    const -> Point3f;
  auto operator * (const Vector3f& v)    const -> Vector3f;
  auto operator * (const Normal3f& n)    const -> Normal3f;
  auto operator * (const Ray&      ray)  const -> Ray;
  auto operator * (const Bounds3f& bbox) const -> Bounds3f;


  /* Transform public methods */
 public:
  // This method throw a exception
  auto At (unsigned int row, unsigned int col) const -> Float;
  auto At (unsigned int row, unsigned int col)       -> Float;

  // Return matrix
  auto GetMatrix    () const -> Matrix4x4;
  auto GetInvMatrix () const -> Matrix4x4;

  auto Row        (unsigned int idx)                            const -> std::array<Float, 4>;
  auto SetRow     (unsigned int idx, std::array<Float, 4>& row)       -> void;
  auto SwapRow    (unsigned int row0, unsigned int row1)              -> void;

  auto Column     (unsigned int idx)                            const -> std::array<Float, 4>;
  auto SetColumn  (unsigned int idx, std::array<Float, 4>& col)       -> void;
  auto SwapColumn (unsigned int col0, unsigned int col1)              -> void;

  auto IsIdentity () const -> bool;
  auto ToIdentity ()       -> void;


  /* Transform private data */
 private:
  Matrix4x4 matrix_;
  Matrix4x4 inv_matrix_;
};


// ---------------------------------------------------------------------------
// Global functions for Transform class
// ---------------------------------------------------------------------------
auto Translate (const Vector3f& delta)             -> Transform;
auto Scale     (Float x, Float y, Float z)         -> Transform;
auto RotateX   (Float theta)                       -> Transform;
auto RotateY   (Float theta)                       -> Transform;
auto RotateZ   (Float theta)                       -> Transform;
auto Rotate    (Float theta, const Vector3f& axis) -> Transform;
auto LookAt    (const Point3f&  position,
                const Point3f&  look,
                const Vector3f& up)                -> Transform;

} // namespace niepce

#endif //_TRANSFORM_H_
