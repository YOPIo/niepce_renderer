#ifndef _TRANSFORM_H_
#define _TRANSFORM_H_

#include "../core/niepce.h"
#include "../geometries/matrix4x4.h"

namespace niepce
{

class Transform
{
 public:
  Transform()
  {
    m_[0][0] = 1.f, m_[0][1] = 0.f, m_[0][2] = 0.f, m_[0][3] = 0.f;
    m_[1][0] = 0.f, m_[1][1] = 1.f, m_[1][2] = 0.f, m_[1][3] = 0.f;
    m_[2][0] = 0.f, m_[2][1] = 0.f, m_[2][2] = 1.f, m_[2][3] = 0.f;
    m_[3][0] = 0.f, m_[3][1] = 0.f, m_[3][2] = 0.f, m_[3][3] = 1.f;
  };
  Transform(Float m00, Float m01, Float m02, Float m03,
            Float m10, Float m11, Float m12, Float m13,
            Float m20, Float m21, Float m22, Float m23,
            Float m30, Float m31, Float m32, Float m33)
  {
    m_[0][0] = m00, m_[0][1] = m01, m_[0][2] = m02, m_[0][3] = m03;
    m_[1][0] = m11, m_[1][1] = m11, m_[1][2] = m12, m_[1][3] = m13;
    m_[2][0] = m20, m_[2][1] = m21, m_[2][2] = m22, m_[2][3] = m23;
    m_[3][0] = m30, m_[3][1] = m31, m_[3][2] = m32, m_[3][3] = m33;
  }
  Transform(Float m[4][4])
  {
    m_[0][0] = m[0][0], m_[0][1] = m[0][1], m_[0][2] = m[0][2], m_[0][3] = m[0][3];
    m_[1][0] = m[1][0], m_[1][1] = m[1][1], m_[1][2] = m[1][2], m_[1][3] = m[1][3];
    m_[2][0] = m[2][0], m_[2][1] = m[2][1], m_[2][2] = m[2][2], m_[2][3] = m[2][3];
    m_[3][0] = m[3][0], m_[3][1] = m[3][1], m_[3][2] = m[3][2], m_[3][3] = m[3][3];
  }
  Transform(const std::array<std::array<Float, 4>, 4>& m)
  {
    m_[0][0] = m[0][0], m_[0][1] = m[0][1], m_[0][2] = m[0][2], m_[0][3] = m[0][3];
    m_[1][0] = m[1][0], m_[1][1] = m[1][1], m_[1][2] = m[1][2], m_[1][3] = m[1][3];
    m_[2][0] = m[2][0], m_[2][1] = m[2][1], m_[2][2] = m[2][2], m_[2][3] = m[2][3];
    m_[3][0] = m[3][0], m_[3][1] = m[3][1], m_[3][2] = m[3][2], m_[3][3] = m[3][3];
  }
  Transform(const Matrix4x4f& m)
  {
    m_[0][0] = m[0][0], m_[0][1] = m[0][1], m_[0][2] = m[0][2], m_[0][3] = m[0][3];
    m_[1][0] = m[1][0], m_[1][1] = m[1][1], m_[1][2] = m[1][2], m_[1][3] = m[1][3];
    m_[2][0] = m[2][0], m_[2][1] = m[2][1], m_[2][2] = m[2][2], m_[2][3] = m[2][3];
    m_[3][0] = m[3][0], m_[3][1] = m[3][1], m_[3][2] = m[3][2], m_[3][3] = m[3][3];
  }
  virtual ~Transform()
  {}
  Transform(const Transform& t) = default;
  Transform(Transform&&      t) = default;
  auto operator = (const Transform& t) -> Transform& = default;
  auto operator = (Transform&&      t) -> Transform& = default;

  auto operator == (const Transform& t) const -> bool
  {
    return t.m_ == m_;
  }
  auto operator != (const Transform& t) const -> bool
  {
    return t.m_ != m_;
  }

  auto operator [] (unsigned int idx) const -> std::array<Float, 4>
  {
    Assertf(idx >= 4, "Out of bounds.");
    if (idx == 0) { return m_[0];  }
    if (idx == 1) { return m_[1];  }
    if (idx == 2) { return m_[2];  }
    return m_[3];
  }
  auto operator [] (unsigned int idx) -> std::array<Float, 4>&
  {
    Assertf(idx >= 4, "Out of bounds.");
    if (idx == 0) { return m_[0];  }
    if (idx == 1) { return m_[1];  }
    if (idx == 2) { return m_[2];  }
    return m_[3];
  }

  // Applying transformatiuons
  // niepce renderer follows right hand coordinate system
  template <typename T>
  auto operator * (const Point3<T>& p) -> Point3<T>
  {
    const T x = p.x, y = p.y, z = p.z;
    const T px = m_[0][0] * x + m_[0][1] * y + m_[0][2] * z + m_[0][3];
    const T py = m_[1][0] * x + m_[1][1] * y + m_[1][2] * z + m_[1][3];
    const T pz = m_[2][0] * x + m_[2][1] * y + m_[2][2] * z + m_[2][3];
    const T pw = m_[3][0] * x + m_[3][1] * y + m_[3][2] * z + m_[3][3];
    return pw == 1 ? Point3<T>(px, py, pz) : Point3<T>(px, py, pz) / pw;
  }
  template <typename T>
  auto operator * (const Vector3<T>& v) -> Vector3<T>
  {
    const T x = v.x, y = v.y, z = v.z;
    return Vector3<T>(m_[0][0] * x + m_[0][1] * y + m_[0][2] * z + m_[0][3],
                      m_[1][0] * x + m_[1][1] * y + m_[1][2] * z + m_[1][3],
                      m_[2][0] * x + m_[2][1] * y + m_[2][2] * z + m_[2][3],
                      m_[3][0] * x + m_[3][1] * y + m_[3][2] * z + m_[3][3]);
  }
  template <typename T>
  auto operator * (const Normal3<T>& n) -> Normal3<T>
  {

  }



  auto GetMatrix() const -> Matrix4x4f
  {
    return m_;
  }
  auto GetInvMatrix() const -> Matrix4x4f = delete;
  auto IsIdentity() const -> bool
  {
    return (m_[0][0] == 1.f && m_[0][1] == 0.f && m_[0][2] == 0.f && m_[0][3] == 0.f &&
            m_[1][0] == 0.f && m_[1][1] == 1.f && m_[1][2] == 0.f && m_[1][3] == 0.f &&
            m_[2][0] == 0.f && m_[2][1] == 0.f && m_[2][2] == 1.f && m_[2][3] == 0.f &&
            m_[3][0] == 0.f && m_[3][1] == 0.f && m_[3][2] == 0.f && m_[3][3] == 1.f);
  }

 private:
  Matrix4x4f m_;
  /*
    Matrix4x4f inv_m_;
  */
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
