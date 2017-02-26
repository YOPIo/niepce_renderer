#include "transform.h"

namespace niepce
{

auto Translate(const Vector3f& delta) -> Transform
{
  return Transform(1.f, 0.f, 0.f, delta.x,
                   0.f, 1.f, 0.f, delta.y,
                   0.f, 0.f, 1.f, delta.z,
                   0.f, 0.f, 0.f,     1.f);

  /*
    inv m
    Transform(1.f, 0.f, 0.f, -delta.x,
              0.f, 1.f, 0.f, -delta.y,
              0.f, 0.f, 1.f, -delta.z,
              0.f, 0.f, 0.f,      1.f);
  */
}

auto Scale(Float x, Float y, Float z) -> Transform
{
  return Transform(  x, 0.f, 0.f, 0.f,
                   0.f,   y, 0.f, 0.f,
                   0.f, 0.f,   z, 0.f,
                   0.f, 0.f, 0.f, 1.f);

  /*
  return Transform(1/x, 0.f, 0.f, 0.f,
                   0.f, 1/y, 0.f, 0.f,
                   0.f, 0.f, 1/z, 0.f,
                   0.f, 0.f, 0.f, 1.f);
   */
}

auto RotateX(Float theta) -> Transform
{
  const Float sin_t = std::sin( Radians(theta) );
  const Float cos_t = std::cos( Radians(theta) );
  return Transform(1.f,   0.f,   0.f,  0.f,
                   0.f, cos_t, -sin_t, 0.f,
                   0.f, sin_t,  cos_t, 0.f,
                   0.f,   0.f,   0.f,  1.f);
}

auto RotateY(Float theta) -> Transform
{
  const Float sin_t = std::sin( Radians(theta) );
  const Float cos_t = std::cos( Radians(theta) );
  return Transform( cos_t, 0.f, sin_t, 0.f,
                      0.f, 1.f,   0.f, 0.f,
                   -sin_t, 0.f, cos_t, 0.f,
                      0.f, 0.f,   0.f, 1.f);
}

auto RotateZ(Float theta) -> Transform
{
  const Float sin_t = std::sin( Radians(theta) );
  const Float cos_t = std::cos( Radians(theta) );
  return Transform(cos_t, -sin_t, 0.f, 0.f,
                   sin_t,  cos_t, 0.f, 0.f,
                     0.f,    0.f, 1.f, 0.f,
                     0.f,    0.f, 0.f, 1.f);
}

// Rodriguez rotation formula
auto Rotate(Float theta, const Vector3f& axis) -> Transform
{
  const Vector3f     n = Normalize(axis);
  const    Float sin_t = std::sin( Radians(theta) );
  const    Float cos_t = std::cos( Radians(theta) );
  const    Float     c = (1.f - cos_t);

  Matrix4x4f ret;
  ret[0][0] = n.x * n.x * c + cos_t;
  ret[0][1] = n.x * n.y * c - n.z * sin_t;
  ret[0][2] = n.z * n.x * c + n.y * sin_t;
  ret[0][3] = 0.f;

  ret[1][0] = n.x * n.y * c + n.z * sin_t;
  ret[1][1] = n.y * n.y * c + cos_t;
  ret[1][2] = n.y * n.z * c - n.x * sin_t;
  ret[1][3] = 0.f;

  ret[2][0] = n.z * n.x * c + n.y * sin_t;
  ret[2][1] = n.y * n.z * c + n.x * sin_t;
  ret[2][2] = n.z * n.z * c + cos_t;
  ret[2][3] = 0.f;

  ret[3][0] = 0.f;
  ret[3][1] = 0.f;
  ret[3][2] = 0.f;
  ret[3][3] = 1.f;

  return Transform(ret);
}

auto LookAt(const Point3f&  position,
            const Point3f&  target,
            const Vector3f& up) -> Transform
{
  Vector3f ez = Normalize(target - position);
  Vector3f ex = Normalize( Cross(up, ez) );
  Vector3f ey = Normalize( Cross(ez, ex) );

  return Transform(ex.x, ey.x, ez.x, position.x,
                   ex.y, ey.y, ez.y, position.y,
                   ex.z, ey.z, ez.z, position.z,
                    0.f,  0.f,  0.f,        1.f);
}

} // namespace niepce
