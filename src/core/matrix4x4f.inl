#include "matrix4x4f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Constructors
// ---------------------------------------------------------------------------
*/
Matrix4x4f::Matrix4x4f ()
{
  *this = Identity ();
}
/*
// ---------------------------------------------------------------------------
*/
Matrix4x4f::Matrix4x4f (Float m) :
    m00 (m), m01 (m), m02 (m), m03 (m),
    m10 (m), m11 (m), m12 (m), m13 (m),
    m20 (m), m21 (m), m22 (m), m23 (m),
    m30 (m), m31 (m), m32 (m), m33 (m)
{}
/*
// ---------------------------------------------------------------------------
*/
Matrix4x4f::Matrix4x4f (Float _m00, Float _m01, Float _m02, Float _m03,
                        Float _m10, Float _m11, Float _m12, Float _m13,
                        Float _m20, Float _m21, Float _m22, Float _m23,
                        Float _m30, Float _m31, Float _m32, Float _m33) :
    m00 (_m00), m01 (_m01), m02 (_m02), m03 (_m03),
    m10 (_m10), m11 (_m11), m12 (_m12), m13 (_m13),
    m20 (_m20), m21 (_m21), m22 (_m22), m23 (_m23),
    m30 (_m30), m31 (_m31), m32 (_m32), m33 (_m33)
{}
/*
// ---------------------------------------------------------------------------
// Operators
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator () (unsigned row, unsigned col) const -> Float
{
  return elements[col * 4 + row];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator () (unsigned row, unsigned col) -> Float&
{
  return elements[col * 4 + row];
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator += (const Matrix4x4f& mat) -> Matrix4x4f&
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      (*this)(i, j) += mat (i, j);
    }
  }
  return (*this);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator -= (const Matrix4x4f& mat) -> Matrix4x4f&
{
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) -= mat (i, j);
      }
    }
    return (*this);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator *= (const Matrix4x4f& mat) -> Matrix4x4f&
{
  for (int i = 0; i < 4; ++i)
  {
    for (int j = 0; j < 4; ++j)
    {
      (*this)(i, j) = (*this)(i, 0) * mat(0, j) + (*this)(i, 1) * mat(i, 1)
                    + (*this)(i, 2) * mat(2, j) + (*this)(i, 3) * mat(i, 3);
    }
  }
  return *this;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::operator *= (Float scale) -> Matrix4x4f&
{
  for (int i = 0; i < 16; ++i)
  {
    (*this).elements[i] *= scale;
  }
  return *this;
}
/*
// ---------------------------------------------------------------------------
// Method
// ---------------------------------------------------------------------------
*/
inline auto Matrix4x4f::HasNaN () const -> bool
{
  for (int i = 0; i < 16; ++i)
  {
    if (std::isnan (elements[i])) { return true; }
  }
  return false;
}
/*
// ---------------------------------------------------------------------------
// Global operators for Matrix4x4f
// ---------------------------------------------------------------------------
*/
inline auto operator == (const Matrix4x4f& rhs, const Matrix4x4f& lhs) -> bool
{
  for (uint32_t r = 0; r < 4; ++r)
  {
    for (uint32_t l = 0; l < 4; ++l)
    {
      if (rhs (r, l) != lhs (r, l)) { return false; }
    }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator != (const Matrix4x4f& rhs, const Matrix4x4f& lhs) -> bool
{
  return !(rhs == lhs);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator + (const Matrix4x4f& rhs, const Matrix4x4f& lhs)
    -> Matrix4x4f
{
  Matrix4x4f mat;
  for (uint32_t i = 0; i < 4; ++i)
  {
    for (uint32_t j = 0; j < 4; ++j)
    {
      mat (i, j) = rhs (i, j) + lhs (i, j);
    }
  }
  return mat;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator - (const Matrix4x4f& rhs, const Matrix4x4f& lhs)
    -> Matrix4x4f
{
  Matrix4x4f mat;
  for (uint32_t i = 0; i < 4; ++i)
  {
    for (uint32_t j = 0; j < 4; ++j)
    {
      mat (i, j) = rhs (i, j) - lhs (i, j);
    }
  }
  return mat;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Matrix4x4f& rhs, const Matrix4x4f& lhs)
    -> Matrix4x4f
{
  Matrix4x4f mat;
  for (uint32_t i = 0; i < 4; ++i)
  {
    for (uint32_t j = 0; j < 4; ++j)
    {
      mat (i, j) = rhs (i, 0) * lhs (0, j)
                 + rhs (i, 1) * lhs (i, 1)
                 + rhs (i, 2) * lhs (2, j)
                 + rhs (i, 3) * lhs (i, 3);
    }
  }
  return mat;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Matrix4x4f& rhs, const Vector3f& lhs) -> Vector3f
{
  const Vector4f vec (lhs.x, lhs.y, lhs.z, 0.0);
  const Vector4f res = rhs * vec;
  return Vector3f (res.x, res.y, res.z);
}
/*
// ---------------------------------------------------------------------------
*/
inline auto operator * (const Matrix4x4f& rhs, const Vector4f& lhs) -> Vector4f
{
  Vector4f vec;
  for (uint32_t r = 0; r < 4; ++r)
  {
    for (uint32_t l = 0; l < 4; ++l)
    {
      vec[r] += rhs (r, l) * lhs[r];
    }
  }
  return vec;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Matrix4x4f& mat, Float scl) -> Matrix4x4f
{
  Matrix4x4f res (mat);
  for (int r = 0; r < 4; ++r)
  {
    for (int l = 0; l < 4; ++l)
    {
      res (r, l) = res (r, l) * scl;
    }
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (Float scale, const Matrix4x4f& mat) -> Matrix4x4f
{
  return mat * scale;
}
/*
// ---------------------------------------------------------------------------
// Util function implementations
// ---------------------------------------------------------------------------
*/
auto Inverse (const Matrix4x4f& mat) -> Matrix4x4f
{
  Float buf;
  Matrix4x4f tmp (mat);
  Matrix4x4f ret;
  for(int i = 0; i < 4; ++i)
  {
    buf = 1.0 / tmp (i, i);
    if (std::isnan (buf))
    {
      // TODO: error
    }
    for(int j = 0; j < 4; ++j)
    {
      tmp (i, j) *= buf;
      ret (i, j) *= buf;
    }
    for(int j = 0; j < 4; ++j)
    {
      if(i != j)
      {
        buf = tmp (j, i);
        for(int k = 0; k < 4; ++k)
        {
          tmp (j, k) -= tmp (i, k) * buf;
          ret (j, k) -= ret (i, k) * buf;
        }
      }
    }
  }
  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
