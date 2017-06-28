#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_

#include "../core/niepce.h"

namespace niepce
{

// ---------------------------------------------------------------------------
// Right hand coordinate system
// ---------------------------------------------------------------------------

class Matrix4x4
{
  /* Matrix public constructor */
 public:
  Matrix4x4 ()
  {
    this->ToIdentity();
  };
  Matrix4x4 (Float m00, Float m01, Float m02, Float m03,
             Float m10, Float m11, Float m12, Float m13,
             Float m20, Float m21, Float m22, Float m23,
             Float m30, Float m31, Float m32, Float m33) :
      matrix ({m00, m10, m20, m30,
               m01, m11, m21, m31,
               m02, m12, m22, m32,
               m03, m13, m23, m33})
  {}
  virtual ~Matrix4x4 ()
  {}

  Matrix4x4 (const Matrix4x4&  m) = default;
  Matrix4x4 (      Matrix4x4&& m) = default;


  /* Matrix public operators */
 public:
  auto operator = (const Matrix4x4&  m) -> Matrix4x4& = default;
  auto operator = (      Matrix4x4&& m) -> Matrix4x4& = default;

  auto operator == (const Matrix4x4& m) const -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0 ; j < 4; ++j)
      {
        if ((*this)(i, j) != m (i, j)) { return false; }
      }
    }
    return true;
  }
  auto operator != (const Matrix4x4& m) const -> bool
  {
    return !(*this == m);
  }

  // Floathis function is not throw a exception
  inline auto operator () (unsigned int row, unsigned int col) const -> Float
  {
    return matrix[col * 4 + row];
  }
  inline auto operator () (unsigned int row, unsigned int col) -> Float&
  {
    return matrix[col * 4 + row];
  }

  auto operator + (const Matrix4x4& m) const -> Matrix4x4
  {
    return Matrix4x4 ((*this)(0, 0) + m(0, 0), (*this)(0, 1) + m(0, 1), (*this)(0, 2) + m(0, 2), (*this)(0, 3) + m(0, 2),
                      (*this)(1, 0) + m(1, 0), (*this)(1, 1) + m(1, 1), (*this)(1, 2) + m(1, 2), (*this)(1, 3) + m(1, 2),
                      (*this)(2, 0) + m(2, 0), (*this)(2, 1) + m(2, 1), (*this)(2, 2) + m(2, 2), (*this)(2, 3) + m(2, 2),
                      (*this)(3, 0) + m(3, 0), (*this)(3, 1) + m(3, 1), (*this)(3, 2) + m(3, 2), (*this)(3, 3) + m(3, 2));
  }
  auto operator += (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) += m (i, j);
      }
    }
    return (*this);
  }

  auto operator - (const Matrix4x4& m) const -> Matrix4x4
  {
    return Matrix4x4 ((*this)(0, 0) - m(0, 0), (*this)(0, 1) - m(0, 1), (*this)(0, 2) - m(0, 2), (*this)(0, 3) - m(0, 2),
                      (*this)(1, 0) - m(1, 0), (*this)(1, 1) - m(1, 1), (*this)(1, 2) - m(1, 2), (*this)(1, 3) - m(1, 2),
                      (*this)(2, 0) - m(2, 0), (*this)(2, 1) - m(2, 1), (*this)(2, 2) - m(2, 2), (*this)(2, 3) - m(2, 2),
                      (*this)(3, 0) - m(3, 0), (*this)(3, 1) - m(3, 1), (*this)(3, 2) - m(3, 2), (*this)(3, 3) - m(3, 2));
  }
  auto operator -= (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) -= m(i, j);
      }
    }
    return (*this);
  }

  auto operator * (const Matrix4x4& m) const -> Matrix4x4
  {
    Matrix4x4 ret;
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        ret (i, j) = (*this)(i, 0) * m(0, j) + (*this)(i, 1) * m(i, 1) + (*this)(i, 2) * m(2, j) + (*this)(i, 3) * m(i, 3);
      }
    }
    return ret;
  }
  auto operator * (Float v) const -> Matrix4x4
  {
    Matrix4x4 ret;
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        ret(i, j) = (*this)(i, j) * v;
      }
    }
    return ret;
  }
  auto operator *= (const Matrix4x4& m) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) = (*this)(i, 0) * m(0, j) + (*this)(i, 1) * m(i, 1) + (*this)(i, 2) * m(2, j) + (*this)(i, 3) * m(i, 3);
      }
    }
    return *this;
  }
  auto operator *= (Float v) -> Matrix4x4&
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        (*this)(i, j) *= v;
      }
    }
    return *this;
  }


  /* Matrix4x4 public methods */
  // FloatODO: Floathrow a out of range exception
 public:
  auto At (unsigned int row, unsigned int col) const -> Float
  {
#ifdef Debug
    // TODO: Range check
#else
    return matrix[col * 4 + row];
#endif // Debug
  }
  auto At (unsigned int row, unsigned int col) -> Float&
  {
#ifdef Debug
    // TODO: Range check
#else
    return matrix[col * 4 + row];
#endif // Debug
  }

  auto ToIdentity () -> void
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if (i == j) { (*this)(i, j) = 1; continue; }
        (*this)(i, j) = 0;
      }
    }
  }

  auto HasNaNs () -> bool
  {
    for (int i = 0; i < 4; ++i)
    {
      for (int j = 0; j < 4; ++j)
      {
        if ( IsNaN( (*this)(i, j) ) ) { return true; }
      }
    }
    return false;
  }


  /*
    Matrix4x4 public data
    It followes right hand coordinate system
  */
 public:
  union
  {
    std::array<Float, 16> matrix;
    struct
    {
      union
      {
        std::array<Float, 4> col0;
        Float m00, m10, m20, m30;
      };
      union
      {
        std::array<Float, 4> col1;
        Float m01, m11, m21, m31;
      };
      union
      {
        std::array<Float, 4> col2;
        Float m02, m12, m22, m32;
      };
      union
      {
        std::array<Float, 4> col3;
        Float m03, m13, m23, m33;
      };
    };
  };

}; // class Matrix4x4


// ---------------------------------------------------------------------------
// Global inline function
// ---------------------------------------------------------------------------
inline auto operator << (std::ostream& os, const Matrix4x4& m) -> std::ostream&
{
  // FIXME:
  os << "matrix: \n";
  os << "[" << m(0, 0) << ", " << m(0, 1) << ", " << m(0, 2) << ", " << m(0, 3) << "]\n";
  os << "[" << m(1, 0) << ", " << m(1, 1) << ", " << m(1, 2) << ", " << m(1, 3) << "]\n";
  os << "[" << m(2, 0) << ", " << m(2, 1) << ", " << m(2, 2) << ", " << m(2, 3) << "]\n";
  os << "[" << m(3, 0) << ", " << m(3, 1) << ", " << m(3, 2) << ", " << m(3, 3) << "]\n";

  return os;
}


// ---------------------------------------------------------------------------
// Global functions for Matrix4x4
// ---------------------------------------------------------------------------
auto Inverse (const Matrix4x4& m) -> Matrix4x4;
auto Transpose (const Matrix4x4& m) -> Matrix4x4;

} // namespace niepce

#endif // _MATRIX4X4_H_
