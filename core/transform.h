#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../core/boundingbox2.h"
#include "../core/boundingbox3.h"
#include "../core/niepce.h"
#include "../core/ray.h"
#include "../geometries/matrix4x4.h"
#include "../geometries/normal3.h"
#include "../geometries/point2.h"
#include "../geometries/point3.h"
#include "../geometries/point4.h"
#include "../geometries/vector2.h"
#include "../geometries/vector3.h"
#include "../geometries/vector4.h"

namespace niepce
{

class Transform
{
 public:
  Transform();
  Transform(Float m00, Float m01, Float m02, Float m03,
            Float m10, Float m11, Float m12, Float m13,
            Float m20, Float m21, Float m22, Float m23,
            Float m30, Float m31, Float m32, Float m33);
  Transform(const Matrix4x4f& m);
  virtual ~Transform();

  Transform(const Transform& t) = default;
  Transform(Transform&&      t) = default;
  auto operator = (const Transform& t) -> Transform& = default;
  auto operator = (Transform&&      t) -> Transform& = default;

  auto operator == (const Transform& t) const -> bool;
  auto operator != (const Transform& t) const -> bool;

  auto operator [] (unsigned int idx) const -> Vector4f;
  auto operator [] (unsigned int idx)       -> Vector4f&;

  // Applying transformatiuons
  // niepce renderer follows right hand coordinate system
  auto operator * (const Point3f& p)    const -> Point3f;
  auto operator * (const Vector3f& v)   const -> Vector3f;
  auto operator * (const Normal3f& n)   const -> Normal3f;
  auto operator * (const Ray& ray)      const -> Ray;
  auto operator * (const BBox3f& bbox) const -> BBox3f;


  auto GetMatrix()    const -> Matrix4x4f;
  auto GetInvMatrix() const -> Matrix4x4f;
  auto IsIdentity()   const -> bool;
  auto ToIdentity()         -> void;

 private:
  Matrix4x4f m_;
  Matrix4x4f inv_m_;
};

/*
  Global functions for Transform class
*/
auto Translate(const Vector3f& delta) -> Transform;
auto Scale(Float x, Float y, Float z) -> Transform;
auto RotateX(Float theta)             -> Transform;
auto RotateY(Float theta)             -> Transform;
auto RotateZ(Float theta)             -> Transform;
auto Rotate(Float theta, const Vector3f& axis) -> Transform;
auto LookAt(const Point3f&  position,
            const Point3f&  look,
            const Vector3f& up) -> Transform;

} // namespace niepce

#endif //_TRANSFORM_H_
