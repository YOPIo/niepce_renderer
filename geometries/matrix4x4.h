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
    mat00 = mat01 = mat02 = mat03 = 0;
    mat10 = mat11 = mat12 = mat13 = 0;
    mat20 = mat21 = mat22 = mat23 = 0;
    mat30 = mat31 = mat32 = mat33 = 0;
  };
  Matrix4x4(T m00, T m01, T m02, T m03,
            T m10, T m11, T m12, T m13,
            T m20, T m21, T m22, T m23,
            T m30, T m31, T m32, T m33)
  {
    mat00 = m00, mat01 = m01, mat02 = m02, mat03 = m03;
    mat10 = m11, mat11 = m11, mat12 = m12, mat13 = m13;
    mat20 = m20, mat21 = m21, mat22 = m22, mat23 = m23;
    mat30 = m30, mat31 = m31, mat32 = m32, mat33 = m33;
  }
  Matrix4x4(T m[4][4])
  {
    mat00 = m[0][0], mat01 = m[0][1], mat02 = m[0][2], mat03 = m[0][3];
    mat10 = m[1][0], mat11 = m[1][1], mat12 = m[1][2], mat13 = m[1][3];
    mat20 = m[2][0], mat21 = m[2][1], mat22 = m[2][2], mat23 = m[2][3];
    mat30 = m[3][0], mat31 = m[3][1], mat32 = m[3][2], mat33 = m[3][3];
  }
  Matrix4x4(const std::array<std::array<T, 4>, 4>& m)
  {
    mat00 = m[0][0], mat01 = m[0][1], mat02 = m[0][2], mat03 = m[0][3];
    mat10 = m[1][0], mat11 = m[1][1], mat12 = m[1][2], mat13 = m[1][3];
    mat20 = m[2][0], mat21 = m[2][1], mat22 = m[2][2], mat23 = m[2][3];
    mat30 = m[3][0], mat31 = m[3][1], mat32 = m[3][2], mat33 = m[3][3];
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
        if ((*this)[i][j] != m[i][j]) { return false; }
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
        if ((*this)[i][j] != m[i][j]) { return true; }
      }
    }
    return false;
  }

  auto operator [] (const unsigned int idx) const -> Vector4<T>
  {
    Assertf(idx < 0 && idx > 4, "Out of range [0, 3].");
    if (idx == 0) { return Vector4<T>(mat00, mat01, mat02, mat03); }
    if (idx == 1) { return Vector4<T>(mat10, mat11, mat12, mat13); }
    if (idx == 2) { return Vector4<T>(mat20, mat21, mat22, mat23); }
    return Vector4<T>(mat30, mat31, mat32, mat33);
  }
  auto operator [] (const unsigned int idx) -> std::array<T, 4>&
  {
    Assertf(idx < 0 && idx > 4, "Out of range [0, 3].");
    if (idx == 0) { return Vector4<T>(mat00, mat01, mat02, mat03); }
    if (idx == 1) { return Vector4<T>(mat10, mat11, mat12, mat13); }
    if (idx == 2) { return Vector4<T>(mat20, mat21, mat22, mat23); }
    return Vector4<T>(mat30, mat31, mat32, mat33);
  }

  auto operator + (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    return Matrix4x4<T>((*this)[0][0] + m[0][0], (*this)[0][1] + m[0][1], (*this)[0][2] + m[0][2], (*this)[0][3] + m[0][3],
                        (*this)[1][0] + m[1][0], (*this)[1][1] + m[1][1], (*this)[1][2] + m[1][2], (*this)[1][3] + m[1][3],
                        (*this)[2][0] + m[2][0], (*this)[2][1] + m[2][1], (*this)[2][2] + m[2][2], (*this)[2][3] + m[2][3],
                        (*this)[3][0] + m[3][0], (*this)[3][1] + m[3][1], (*this)[3][2] + m[3][2], (*this)[3][3] + m[3][3]);
  }
  auto operator += (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)[i][j] += m[i][j];
      }
    }
    return (*this);
  }

  auto operator - (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    return Matrix4x4<T>((*this)[0][0] - m[0][0], (*this)[0][1] - m[0][1], (*this)[0][2] - m[0][2], (*this)[0][3] - m[0][3],
                        (*this)[1][0] - m[1][0], (*this)[1][1] - m[1][1], (*this)[1][2] - m[1][2], (*this)[1][3] - m[1][3],
                        (*this)[2][0] - m[2][0], (*this)[2][1] - m[2][1], (*this)[2][2] - m[2][2], (*this)[2][3] - m[2][3],
                        (*this)[3][0] - m[3][0], (*this)[3][1] - m[3][1], (*this)[3][2] - m[3][2], (*this)[3][3] - m[3][3]);
  }
  auto operator -= (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
    Warningf(m.HasNaNs(), "Detected NaN.");
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)[i][j] -= m[i][j];
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
        ret[i][j] = (*this)[i][0] * m[0][j] + (*this)[i][1] * m[1][j] + (*this)[i][2] * m[2][j] + (*this)[i][3] * m[3][j];
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
        ret[i][j] = (*this)[i][j] * v;
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
        (*this)[i][j] = (*this)[i][0] * m[0][j] + (*this)[i][1] * m[1][j] + (*this)[i][2] * m[2][j] + (*this)[i][3] * m[3][j];
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
        (*this)[i][j] *= v;
      }
    }
    return *this;
  }

  auto Row(unsigned int row) -> Vector4<T>
  {
    Assertf(row >= 4, "Out of range [0, 3].");
    if (row == 0) { Vector4<T>(mat00, mat01, mat02, mat03); }
    if (row == 1) { Vector4<T>(mat10, mat11, mat12, mat13); }
    if (row == 2) { Vector4<T>(mat20, mat21, mat22, mat23); }
    return Vector4<T>(mat30, mat31, mat32, mat33);
  }
  auto Column(unsigned int col) -> Vector4<T>
  {
    return (*this)[col];
  }

  auto SwapRows(unsigned int row0, unsigned int row1) -> void
  {
    Vector4<T> temp = Row(row0);
    SetRow(row0, Row(row1));
    SetRow(row1, temp);
  }
  auto SwapColumns(unsigned int col0, unsigned int col1) -> void
  {
    Vector4<T> temp = (*this)[col0];
    (*this)[col0] = (*this)[col1];
    (*this)[col1] = temp;
  }

 private:
  auto SetRow(unsigned int row, const Vector4<T>& v) -> void
  {
    Assertf(row >= 4, "Out of range [0, 3].");
    col0[row] = v[0];
    col1[row] = v[1];
    col2[row] = v[2];
    col3[row] = v[3];
  }
  auto HasNaNs() -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if ( IsNaN((*this)[i][j]) ) { return true; }
      }
    }
    return false;
  }

 public:
  /*
        |m00 m01 m02 m03|
    M = |m10 m11 m12 m13|
        |m20 m21 m22 m23|
        |m30 m31 m23 m33|
   */
  union
  {
    struct { T mat00, mat10, mat20, mat30; };
    Vector4<T> col0;
  };
  union
  {
    struct { T mat01, mat11, mat21, mat31; };
    Vector4<T> col1;
  };
  union
  {
    struct { T mat02, mat12, mat22, mat32; };
    Vector4<T> col2;
  };
  union
  {
    struct { T mat03, mat13, mat23, mat33; };
    Vector4<T> col3;
  };
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
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T>;

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>;

} // namespace niepce

#endif // _MATRIX4X4_H_
