#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "../core/niepce.h"
#include "vector2.h"
#include "vector3.h"
#include "point2.h"
#include "point3.h"

namespace niepce
{

template <typename T>
class Matrix4x4
{
 public:
  Matrix4x4()
  {
    mat[0][0] = mat[0][1] = mat[0][2] = mat[0][3] = 0;
    mat[1][0] = mat[1][1] = mat[1][2] = mat[1][3] = 0;
    mat[2][0] = mat[2][1] = mat[2][2] = mat[2][3] = 0;
    mat[3][0] = mat[3][1] = mat[3][2] = mat[3][3] = 0;
  };
  Matrix4x4(T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33)
  {
    mat[0][0] = m00, mat[0][1] = m01, mat[0][2] = m02, mat[0][3] = m03;
    mat[1][0] = m11, mat[1][1] = m11, mat[1][2] = m12, mat[1][3] = m13;
    mat[2][0] = m20, mat[2][1] = m21, mat[2][2] = m22, mat[2][3] = m23;
    mat[3][0] = m30, mat[3][1] = m31, mat[3][2] = m32, mat[3][3] = m33;
  }
  Matrix4x4(T m[4][4])
  {
    mat[0][0] = m[0][0], mat[0][1] = m[0][1], mat[0][2] = m[0][2], mat[0][3] = m[0][3];
    mat[1][0] = m[1][0], mat[1][1] = m[1][1], mat[1][2] = m[1][2], mat[1][3] = m[1][3];
    mat[2][0] = m[2][0], mat[2][1] = m[2][1], mat[2][2] = m[2][2], mat[2][3] = m[2][3];
    mat[3][0] = m[3][0], mat[3][1] = m[3][1], mat[3][2] = m[3][2], mat[3][3] = m[3][3];
  }
  Matrix4x4(const std::array<std::array<T, 4>, 4>& m)
  {
    mat[0][0] = m[0][0], mat[0][1] = m[0][1], mat[0][2] = m[0][2], mat[0][3] = m[0][3];
    mat[1][0] = m[1][0], mat[1][1] = m[1][1], mat[1][2] = m[1][2], mat[1][3] = m[1][3];
    mat[2][0] = m[2][0], mat[2][1] = m[2][1], mat[2][2] = m[2][2], mat[2][3] = m[2][3];
    mat[3][0] = m[3][0], mat[3][1] = m[3][1], mat[3][2] = m[3][2], mat[3][3] = m[3][3];
  }
  virtual ~Matrix4x4(){}
  Matrix4x4(const Matrix4x4& m) = default;
  Matrix4x4(Matrix4x4&&      m) = default;
  auto operator = (const Matrix4x4& m) -> Matrix4x4& = default;
  auto operator = (Matrix4x4&&      m) -> Matrix4x4& = default;

  auto operator == (const Matrix4x4& m) const -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0 ; j < 4; ++j)
      {
        if (mat[i][j] != m[i][j]) { return false; }
      }
    }
    return true;
  }
  auto operator != (const Matrix4x4& m) const -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0 ; j < 4; ++j)
      {
        if (mat[i][j] != m[i][j]) { return true; }
      }
    }
    return false;
  }

  auto operator [] (const unsigned int idx) const -> std::array<T, 4>
  {
    Assertf(idx < 0 && idx > 4, "Out of bounds.");
    if (idx == 0) { return mat[0]; }
    if (idx == 1) { return mat[1]; }
    if (idx == 2) { return mat[2]; }
    return mat[3];
  }
  auto operator [] (const unsigned int idx) -> std::array<T, 4>&
  {
    Assertf(idx < 0 && idx > 4, "Out of bounds.");
    if (idx == 0) { return mat[0]; }
    if (idx == 1) { return mat[1]; }
    if (idx == 2) { return mat[2]; }
    return mat[3];
  }

  auto operator + (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    return Matrix4x4<T>(mat[0][0] + m[0][0], mat[0][1] + m[0][1], mat[0][2] + m[0][2], mat[0][3] + m[0][3],
                        mat[1][0] + m[1][0], mat[1][1] + m[1][1], mat[1][2] + m[1][2], mat[1][3] + m[1][3],
                        mat[2][0] + m[2][0], mat[2][1] + m[2][1], mat[2][2] + m[2][2], mat[2][3] + m[2][3],
                        mat[3][0] + m[3][0], mat[3][1] + m[3][1], mat[3][2] + m[3][2], mat[3][3] + m[3][3]);
  }
  auto operator += (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        mat[i][j] += m[i][j];
      }
    }
    return (*this);
  }

  auto operator - (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    return Matrix4x4<T>(mat[0][0] - m[0][0], mat[0][1] - m[0][1], mat[0][2] - m[0][2], mat[0][3] - m[0][3],
                        mat[1][0] - m[1][0], mat[1][1] - m[1][1], mat[1][2] - m[1][2], mat[1][3] - m[1][3],
                        mat[2][0] - m[2][0], mat[2][1] - m[2][1], mat[2][2] - m[2][2], mat[2][3] - m[2][3],
                        mat[3][0] - m[3][0], mat[3][1] - m[3][1], mat[3][2] - m[3][2], mat[3][3] - m[3][3]);
  }
  auto operator -= (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        mat[i][j] -= m[i][j];
      }
    }
    return (*this);
  }

  auto operator * (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    Matrix4x4<T> ret;
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        ret[i][j] = mat[i][0] * m[0][j] + mat[i][1] * m[1][j] + mat[i][2] * m[2][j] + mat[i][3] * m[3][j];
      }
    }
  }
  auto operator * (T v) const -> Matrix4x4<T>
  {
    Warningf(IsNaN(v), "Detected NaN.");
    Matrix4x4<T> ret;
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        ret[i][j] = mat[i][j] * v;
      }
    }
    return ret;
  }
  auto operator *= (const Matrix4x4& m) -> Matrix4x4<T>&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        mat[i][j] = mat[i][0] * m[0][j] + mat[i][1] * m[1][j] + mat[i][2] * m[2][j] + mat[i][3] * m[3][j];
      }
    }
    return *this;
  }
  auto operator *= (T v) -> Matrix4x4<T>&
  {
    Warningf(IsNaN(v), "Detected NaN.");
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        mat[i][j] *= v;
      }
    }
    return *this;
  }

  auto HasNaNs() -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if ( IsNaN(mat[i][j]) ) { return true; }
      }
    }
    return false;
  }

 public:
  std::array<std::array<T, 4>, 4> mat;
};

/*
  Global inline function
*/
template <typename T>
inline auto operator << (std::ostream& os, const Matrix4x4<T>& m) -> std::ostream&
{
  os << "[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]\n"
     << "[" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]\n"
     << "[" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]\n"
     << "[" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]\n";
  return os;
}

/*
  Global functions
*/
// todo: implementaion
template <typename T>
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T> = delete;

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>;

} // namespace niepce

#endif // _MATRIX4X4_H_
