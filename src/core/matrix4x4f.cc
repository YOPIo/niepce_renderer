/*!
 * @file matrix4x4.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "matrix4x4f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Matrix4x4f::Matrix4x4f () :
  m_ ()
{
  m_[0][0] = 1.0, m_[0][1] = 0.0, m_[0][2] = 0.0, m_[0][3] = 0.0;
  m_[1][0] = 0.0, m_[1][1] = 1.0, m_[1][2] = 0.0, m_[1][3] = 0.0;
  m_[2][0] = 0.0, m_[2][1] = 0.0, m_[2][2] = 1.0, m_[2][3] = 0.0;
  m_[3][0] = 0.0, m_[3][1] = 0.0, m_[3][2] = 0.0, m_[3][3] = 1.0;
}
/*
// ---------------------------------------------------------------------------
*/
Matrix4x4f::Matrix4x4f (Float m00, Float m01, Float m02, Float m03,
                      Float m10, Float m11, Float m12, Float m13,
                      Float m20, Float m21, Float m22, Float m23,
                      Float m30, Float m31, Float m32, Float m33) :
  m_ ()
{
  m_[0][0] = m00, m_[0][1] = m01, m_[0][2] = m02, m_[0][3] = m03;
  m_[1][0] = m10, m_[1][1] = m11, m_[1][2] = m12, m_[1][3] = m13;
  m_[2][0] = m20, m_[2][1] = m21, m_[2][2] = m22, m_[2][3] = m23;
  m_[3][0] = m30, m_[3][1] = m31, m_[3][2] = m32, m_[3][3] = m33;
}
/*
// ---------------------------------------------------------------------------
*/
auto Matrix4x4f::operator () (unsigned int x, unsigned int y) const noexcept
  -> Float
{
  return m_[x][y];
}
/*
// ---------------------------------------------------------------------------
*/
auto Matrix4x4f::At (unsigned int x, unsigned int y) const -> Float
{
  try { return m_.at (x).at (y); }
  catch (const std::exception& e) { throw e; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Matrix4x4f::SetFloat (unsigned int x, unsigned int y, Float value) -> void
{
  if (4 <= x || 4 <= y)
  {
    throw std::out_of_range ("");
  }
  m_[x][y] = value;
}
/*
// ---------------------------------------------------------------------------
*/
auto Matrix4x4f::Identity () -> Matrix4x4f
{
  return Matrix4x4f ();
}
/*
// ---------------------------------------------------------------------------
// Matrix4x4f
// ---------------------------------------------------------------------------
*/
auto operator == (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool
{
  for (unsigned int i = 0; i < 4; ++i)
  {
    for (unsigned int j = 0; j < 4; ++j)
    {
      if (lhs (i, j) != rhs (i, j)) { return false; }
    }
  }
  return true;
}
/*
// ---------------------------------------------------------------------------
*/
auto operator != (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool
{
  return !(lhs == rhs);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> Matrix4x4f
{
  Matrix4x4f res;
  for (unsigned int i = 0; i < 4; ++i)
  {
    for (unsigned int j = 0; j < 4; ++j)
    {
      const Float value
        = lhs (i, 0) * rhs (0, j) + lhs (i, 1) * rhs (1, j)
        + lhs (i, 2) * rhs (2, j) + lhs (i, 3) * rhs (3, j);
      res.SetFloat (i, j, value);
    }
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
// Matrix4x4f functions
// ---------------------------------------------------------------------------
*/
auto Transpose (const Matrix4x4f& m) -> Matrix4x4f
{
  return Matrix4x4f (m (0, 0), m (1, 0), m (2, 0), m (3, 0),
                     m (0, 1), m (1, 1), m (2, 1), m (3, 1),
                     m (0, 2), m (1, 2), m (2, 2), m (3, 2),
                     m (0, 3), m (1, 3), m (2, 3), m (3, 3) );
}
/*
// ---------------------------------------------------------------------------
*/
auto Inverse (const Matrix4x4f& m) -> Matrix4x4f
{
  int indxc[4];
  int indxr[4];
  int ipiv[4] = {0, 0, 0, 0};
  Float minv[4][4];

  for (unsigned int i = 0; i < 4; ++i)
  {
    for (unsigned int j = 0; j < 4; ++j)
    {
      minv[i][j] = m (i, j);
    }
  }

  for (unsigned int i = 0; i < 4; i++)
  {
    int irow = 0, icol = 0;
    Float big = 0.f;
    // Choose pivot
    for (unsigned int j = 0; j < 4; j++)
    {
      if (ipiv[j] != 1)
      {
        for (unsigned int k = 0; k < 4; k++)
        {
          if (ipiv[k] == 0)
          {
            if (std::abs (minv[j][k]) >= big)
            {
              big = Float (std::abs (minv[j][k]));
              irow = j;
              icol = k;
            }
          }
          else if (ipiv[k] > 1)
          {
            // Inverse matrix is not found.
            std::cerr << " Inverse matrix is not found." << std::endl;
          }
        }
      }
    }

    ++ipiv[icol];
    // Swap rows _irow_ and _icol_ for pivot
    if (irow != icol)
    {
      for (unsigned int k = 0; k < 4; ++k)
      {
        std::swap (minv[irow][k], minv[icol][k]);
      }
    }

    indxr[i] = irow;
    indxc[i] = icol;
    if (minv[icol][icol] == 0.f)
    {
      // Inverse matrix is not found.
      std::cerr << " Inverse matrix is not found." << std::endl;
    }

    // Set $m[icol][icol]$ to one by scaling row _icol_ appropriately
    Float pivinv = 1. / minv[icol][icol];
    minv[icol][icol] = 1.;
    for (unsigned int j = 0; j < 4; j++)
    {
      minv[icol][j] *= pivinv;
    }

    // Subtract this row from others to zero out their columns
    for (unsigned int j = 0; j < 4; j++)
    {
      if (j != icol)
      {
        Float save = minv[j][icol];
        minv[j][icol] = 0;
        for (unsigned int k = 0; k < 4; k++)
        {
          minv[j][k] -= minv[icol][k] * save;
        }
      }
    }
  }
  // Swap columns to reflect permutation
  for (unsigned int j = 3; j >= 0; j--)
  {
    if (indxr[j] != indxc[j])
    {
      for (unsigned int k = 0; k < 4; k++)
      {
        std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
      }
    }
  }

  return Matrix4x4f (minv[0][0], minv[0][1], minv[0][2], minv[0][3],
                     minv[1][0], minv[1][1], minv[1][2], minv[1][3],
                     minv[2][0], minv[2][1], minv[2][2], minv[2][3],
                     minv[3][0], minv[3][1], minv[3][2], minv[3][3]);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

