#include "transform.h"

namespace niepce
{

Transform::Transform () :
    matrix_     ( 1, 0, 0, 0,
                  0, 1, 0, 0,
                  0, 0, 1, 0,
                  0, 0, 0, 1),
    inv_matrix_ ( Inverse(matrix_) )
{}

Transform::Transform (Float m00, Float m01, Float m02, Float m03,
                      Float m10, Float m11, Float m12, Float m13,
                      Float m20, Float m21, Float m22, Float m23,
                      Float m30, Float m31, Float m32, Float m33) :
    matrix_     (Matrix4x4 (m00, m01, m02, m03,
                            m10, m11, m12, m13,
                            m20, m21, m22, m23,
                            m30, m31, m32, m33)),
    inv_matrix_ ( Inverse(matrix_) )
{}

Transform::Transform (const Matrix4x4& m) :
    matrix_     (m),
    inv_matrix_ ( Inverse(m) )
{}

Transform::~Transform ()
{}

auto Transform::operator == (const Transform& t) const -> bool
{
  return t.matrix_ == matrix_;
}

auto Transform::operator != (const Transform& t) const -> bool
{
  return t.matrix_ != matrix_;
}

auto Transform::operator () (unsigned int row, unsigned int col) -> Float
{
  return matrix_(row, col);
}

auto Transform::operator * (const Point3f& p) const -> Point3f
{
  const Float x = p.x, y = p.y, z = p.z;
  const Float px = matrix_ (0, 0) * x + matrix_ (0, 1) * y + matrix_ (0, 2) * z + matrix_ (0, 3);
  const Float py = matrix_ (1, 0) * x + matrix_ (1, 1) * y + matrix_ (1, 2) * z + matrix_ (1, 3);
  const Float pz = matrix_ (2, 0) * x + matrix_ (2, 1) * y + matrix_ (2, 2) * z + matrix_ (2, 3);
  const Float pw = matrix_ (3, 0) * x + matrix_ (3, 1) * y + matrix_ (3, 2) * z + matrix_ (3, 3);
  return pw == 1 ? Point3f(px, py, pz) : Point3f(px, py, pz) / pw;
}

auto Transform::operator * (const Vector3f& v) const -> Vector3f
{
  const Float x = v.x, y = v.y, z = v.z;
  return Vector3f(matrix_ (0, 0) * x + matrix_ (0, 1) * y + matrix_ (0, 2) * z,
                  matrix_ (1, 0) * x + matrix_ (1, 1) * y + matrix_ (1, 2) * z,
                  matrix_ (2, 0) * x + matrix_ (2, 1) * y + matrix_ (2, 2) * z);
}

auto Transform::operator * (const Normal3f& n) const -> Normal3f
{
  const Float x = n.x, y = n.y, z = n.z;
  return Normal3f(inv_matrix_ (0, 0) * x + inv_matrix_ (1, 0) * y + inv_matrix_ (2, 0) * z,
                  inv_matrix_ (0, 1) * x + inv_matrix_ (1, 1) * y + inv_matrix_ (2, 1) * z,
                  inv_matrix_ (0, 2) * x + inv_matrix_ (1, 2) * y + inv_matrix_ (2, 2) * z);
}

auto Transform::operator * (const Ray& ray) const -> Ray
{
  const Point3f  origin    = (*this) * ray.origin;;
  const Vector3f direction = (*this) * ray.direction;
  return Ray(origin, direction);
}

auto Transform::operator * (const Bounds3f& bbox) const -> Bounds3f
{
  const Transform m = *this;
  Bounds3f ret;
  ret = Union (ret, m * Point3f(bbox.Min().x, bbox.Min().y, bbox.Min().z) );
  ret = Union (ret, m * Point3f(bbox.Min().x, bbox.Min().y, bbox.Max().z) );
  ret = Union (ret, m * Point3f(bbox.Min().x, bbox.Max().y, bbox.Min().z) );
  ret = Union (ret, m * Point3f(bbox.Min().x, bbox.Max().y, bbox.Max().z) );
  ret = Union (ret, m * Point3f(bbox.Max().x, bbox.Min().y, bbox.Min().z) );
  ret = Union (ret, m * Point3f(bbox.Max().x, bbox.Min().y, bbox.Max().z) );
  ret = Union (ret, m * Point3f(bbox.Max().x, bbox.Max().y, bbox.Min().z) );
  ret = Union (ret, m * Point3f(bbox.Max().x, bbox.Max().y, bbox.Max().z) );
  return ret;
}

auto Transform::GetMatrix() const -> Matrix4x4
{
  return matrix_;
}

auto Transform::GetInvMatrix() const -> Matrix4x4
{
  return inv_matrix_;
}

auto Transform::IsIdentity() const -> bool
{
  return (matrix_(0, 0) == 1.f && matrix_(0, 1) == 0.f && matrix_(0, 2) == 0.f && matrix_(0, 3) == 0.f &&
          matrix_(1, 0) == 0.f && matrix_(1, 1) == 1.f && matrix_(1, 2) == 0.f && matrix_(1, 3) == 0.f &&
          matrix_(2, 0) == 0.f && matrix_(2, 1) == 0.f && matrix_(2, 2) == 1.f && matrix_(2, 3) == 0.f &&
          matrix_(3, 0) == 0.f && matrix_(3, 1) == 0.f && matrix_(3, 2) == 0.f && matrix_(3, 3) == 1.f);
}

auto Transform::ToIdentity() -> void
{
  matrix_.ToIdentity();
  inv_matrix_ = Inverse ( matrix_ );
}


// ---------------------------------------------------------------------------
// Global functions for Transform class
// ---------------------------------------------------------------------------
auto Translate(const Vector3f& delta) -> Transform
{
  return Transform(1.f, 0.f, 0.f, delta.x,
                   0.f, 1.f, 0.f, delta.y,
                   0.f, 0.f, 1.f, delta.z,
                   0.f, 0.f, 0.f,     1.f);
}

auto Scale(Float x, Float y, Float z) -> Transform
{
  return Transform(  x, 0.f, 0.f, 0.f,
                   0.f,   y, 0.f, 0.f,
                   0.f, 0.f,   z, 0.f,
                   0.f, 0.f, 0.f, 1.f);
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

  Matrix4x4 ret;
  ret (0, 0) = n.x * n.x * c + cos_t;
  ret (0, 1) = n.x * n.y * c - n.z * sin_t;
  ret (0, 2) = n.z * n.x * c + n.y * sin_t;
  ret (0, 3) = 0.f;

  ret (1, 0) = n.x * n.y * c + n.z * sin_t;
  ret (1, 1) = n.y * n.y * c + cos_t;
  ret (1, 2) = n.y * n.z * c - n.x * sin_t;
  ret (1, 3) = 0.f;

  ret (2, 0) = n.z * n.x * c + n.y * sin_t;
  ret (2, 1) = n.y * n.z * c + n.x * sin_t;
  ret (2, 2) = n.z * n.z * c + cos_t;
  ret (2, 3) = 0.f;

  ret (3, 0) = 0.f;
  ret (3, 1) = 0.f;
  ret (3, 2) = 0.f;
  ret (3, 3) = 1.f;

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
