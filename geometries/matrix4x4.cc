#include "matrix4x4.h"

namespace niepce
{

// Calculate inverse matrix M^-1 by LU factorization. (Doolittle)
template <typename T>
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  Matrix4x4<T> ret(m);
  Vector4<T>   v(0, 1, 2, 3);
  int toggle = 1;

  int row, column;
  for (int k = 0; k < 4; ++k)
  {
    // Swapping the column that absolute value of the diagonal component becomes the maximum.
    T colmax = std::fabs(ret[k][k]);
    row = k;
    for (int i = k + 1; i < 4; ++i)
    {
      if (std::fabs(ret[k][i]) > colmax)
      {
        colmax = std::fabs(ret[k][i]);
        row = i;
      }
    }
    // Swap
    if (row != k)
    {
      
    }


  }
}

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  return Matrix4x4<T>(m[0][0], m[1][0], m[2][0], m[3][0],
                      m[0][1], m[1][1], m[2][1], m[3][1],
                      m[0][2], m[1][2], m[2][2], m[3][2],
                      m[0][3], m[1][3], m[2][3], m[3][3]);
}

} // namespace niecpe
