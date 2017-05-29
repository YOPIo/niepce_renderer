#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "../core/niepce.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Logger declaration
// ---------------------------------------------------------------------------
extern std::shared_ptr<spdlog::logger> console;

template <typename T>
class Matrix4x4
{
 public:
  Matrix4x4()
  {
    this->ToIdentity();
  };
  Matrix4x4(T mat00, T mat01, T mat02, T mat03,
            T mat10, T mat11, T mat12, T mat13,
            T mat20, T mat21, T mat22, T mat23,
            T mat30, T mat31, T mat32, T mat33)
  {
    m00 = mat00, m01 = mat01, m02 = mat02 ,m03 = mat03;
    m10 = mat10, m11 = mat11, m12 = mat12 ,m13 = mat13;
    m20 = mat20, m21 = mat21, m22 = mat22 ,m23 = mat23;
    m30 = mat30, m31 = mat31, m32 = mat32 ,m33 = mat33;
  }
  Matrix4x4(const std::array<std::array<T, 4>, 4>& mat)
  {
    m00 = mat[0][0], m01 = mat[0][1], m02 = mat[0][2], m03 = mat[0][3];
    m10 = mat[1][0], m11 = mat[1][1], m12 = mat[1][2], m13 = mat[1][3];
    m20 = mat[2][0], m21 = mat[2][1], m22 = mat[2][2], m23 = mat[2][3];
    m30 = mat[3][0], m31 = mat[3][1], m32 = mat[3][2], m33 = mat[3][3];
  }
  virtual ~Matrix4x4()
  {}

  Matrix4x4(const Matrix4x4& m) = default;
  Matrix4x4(Matrix4x4&&      m) = default;


  // ---------------------------------------------------------------------------
  // Matrix4x4 public operator
  // ---------------------------------------------------------------------------
 public:
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
    return !(*this == m);
  }

  auto operator [] (const std::size_t idx) const -> std::array<T, 4>
  {
#ifdef Debug
    // TODO: Range check
#endif // Debug
    if (idx == 0) { return row0; }
    if (idx == 1) { return row1; }
    if (idx == 2) { return row2; }
    return row3;
  }
  auto operator [] (const std::size_t idx) -> std::array<T, 4>&
  {
#ifdef Debug
    // TODO: Range check
#endif // Debug
    if (idx == 0) { return row0; }
    if (idx == 1) { return row1; }
    if (idx == 2) { return row2; }
    return row3;
  }

  auto operator + (const Matrix4x4<T>& m) const -> Matrix4x4<T>
  {
    return Matrix4x4<T>((*this)[0][0] + m[0][0], (*this)[0][1] + m[0][1], (*this)[0][2] + m[0][2], (*this)[0][3] + m[0][3],
                        (*this)[1][0] + m[1][0], (*this)[1][1] + m[1][1], (*this)[1][2] + m[1][2], (*this)[1][3] + m[1][3],
                        (*this)[2][0] + m[2][0], (*this)[2][1] + m[2][1], (*this)[2][2] + m[2][2], (*this)[2][3] + m[2][3],
                        (*this)[3][0] + m[3][0], (*this)[3][1] + m[3][1], (*this)[3][2] + m[3][2], (*this)[3][3] + m[3][3]);
  }
  auto operator += (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
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
    return Matrix4x4<T>((*this)[0][0] - m[0][0], (*this)[0][1] - m[0][1], (*this)[0][2] - m[0][2], (*this)[0][3] - m[0][3],
                        (*this)[1][0] - m[1][0], (*this)[1][1] - m[1][1], (*this)[1][2] - m[1][2], (*this)[1][3] - m[1][3],
                        (*this)[2][0] - m[2][0], (*this)[2][1] - m[2][1], (*this)[2][2] - m[2][2], (*this)[2][3] - m[2][3],
                        (*this)[3][0] - m[3][0], (*this)[3][1] - m[3][1], (*this)[3][2] - m[3][2], (*this)[3][3] - m[3][3]);
  }
  auto operator -= (const Matrix4x4<T>& m) -> Matrix4x4<T>&
  {
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
    Matrix4x4<T> ret;
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        ret[i][j] = (*this)[i][0] * m[0][j] + (*this)[i][1] * m[1][j] + (*this)[i][2] * m[2][j] + (*this)[i][3] * m[3][j];
      }
    }
    return ret;
  }
  auto operator * (T v) const -> Matrix4x4<T>
  {
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
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)[i][j] *= v;
      }
    }
    return *this;
  }

  auto At(std::size_t row, std::size_t col) const -> T
  {
#ifdef Debug
    if (row >= 4) { throw std::out_of_range("row should be in range[0, 3]."); }
    if (col >= 4) { throw std::out_of_range("column should be in range[0, 3]."); }
    return *(&row0 + row)[col];
#else
    return *(&row0 + row)[col];
#endif // Debug
  }

  auto Row(std::size_t row) const -> std::array<T, 4>
  {
    // TODO: Range check
    return *(&row0 + row);
  }
  auto SetRow(std::size_t idx, const Vector4<T>& row) -> void
  {
    // TODO: Range check
    *(&row0 + idx) = row;
  }
  auto SwapRows(unsigned int r0, unsigned int r1) -> void
  {
    const Vector4<T> temp = Row(r0);
    SetRow(r0, Row(r1));
    SetRow(r1, temp);
  }

  auto Column(unsigned int col) const -> std::array<T, 4>
  {
    // TODO: Range check
    if (col == 0) { return Vector4<T>(m00, m10, m20, m30);  }
    if (col == 1) { return Vector4<T>(m01, m11, m21, m31);  }
    if (col == 2) { return Vector4<T>(m02, m22, m22, m32);  }
    return Vector4<T>(m03, m13, m23, m33);
  }
  auto SetColumn(unsigned int idx, const Vector4<T>& col) -> void
  {
    // TODO: Range check
    row0[idx] = col[0];
    row1[idx] = col[1];
    row2[idx] = col[2];
    row3[idx] = col[3];
  }
  auto SwapColumns(unsigned int c0, unsigned int c1) -> void
  {
    const Vector4<T> temp = Column(c0);
    SetColumn(c0, Column(c1));
    SetColumn(c1, temp);
  }


  // ---------------------------------------------------------------------------
  // Matrix4x4 public methods
  // ---------------------------------------------------------------------------
 public:
  auto ToIdentity() -> void
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if (i == j) { (*this)[i][j] = 1; continue; }
        (*this)[i][j] = 0;
      }
    }
  }

  // ---------------------------------------------------------------------------
  // Matrix private methods
  // ---------------------------------------------------------------------------
 private:
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


  // ---------------------------------------------------------------------------
  // Matrix4x4 public data
  // ---------------------------------------------------------------------------
 public:
    union
    {
      std::array<T, 4> row0;
      struct { T m00, m01, m02, m03; };
    };
    union
    {
      std::array<T, 4> row1;
      struct { T m10, m11, m12, m13; };
    };
    union
    {
      std::array<T, 4> row2;
      struct { T m20, m21, m22, m23; };
    };
    union
    {
      std::array<T, 4> row3;
      struct { T m30, m31, m32, m33; };
    };
}; // class Matrix4x4


// ---------------------------------------------------------------------------
// Global inline function
// ---------------------------------------------------------------------------
template <typename T>
inline auto operator << (std::ostream& os, const Matrix4x4<T>& m) -> std::ostream&
{
  os << "matrix: \n";
  os << "[" << m[0][0] << ", " << m[0][1] << ", " << m[0][2] << ", " << m[0][3] << "]\n";
  os << "[" << m[1][0] << ", " << m[1][1] << ", " << m[1][2] << ", " << m[1][3] << "]\n";
  os << "[" << m[2][0] << ", " << m[2][1] << ", " << m[2][2] << ", " << m[2][3] << "]\n";
  os << "[" << m[3][0] << ", " << m[3][1] << ", " << m[3][2] << ", " << m[3][3] << "]\n";
  return os;
}


// ---------------------------------------------------------------------------
// Global functions
// ---------------------------------------------------------------------------
template <typename T>
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T>;

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>;

} // namespace niepce

#endif // _MATRIX4X4_H_
