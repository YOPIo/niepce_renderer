#include "matrix4x4.h"

namespace niepce
{

// Calculate inverse matrix M^-1 by LU factorization. (Doolittle)
template <typename T>
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  Matrix4x4<T> ret(m);
  Matrix4x4<T> permutation;

  typedef std::pair<int, int> Pair;
  Pair swaped_pairs[4];

  // LU factorization
  for (int k = 0; k < 4; ++k)
  {
    int max_pivot = -1.f;
    int row = 0, col = 0;
    // Swapping the column that absolute value of the diagonal component becomes the maximum.
    T colmax = std::fabs(ret[k][k]);
    // Finding a maximum diagoal component.
    for (int r = k + 1; r < 4; ++r)
    {
      for (int c = k + 1; c < 4; ++c)
      {
        const T abs_p = std::fabs(ret[r][c]);
        if (abs_p > max_pivot)
        {
          row = r, col = c;
          max_pivot = abs_p;
        }
      }
    }

    ret.SwapRows(row, col);
    swaped_pairs[k] = std::make_pair(row, col);

    const T pivot = ret[col][col];
    if (pivot == 0.f) { Warningf(true, "Faild to decompose."); return m; }

    ret[col][col] = 1.f;
    for (int r = 0; r < 4; ++r) { ret[col][r] *= 1.f / pivot; }
    Vector4<T> scaled_row = ret[col];
    for (int r = 0; r < 4; ++r)
    {
      if (r != col)
      {
        T s = ret[r][col];
        ret[r][col] = 0.f;
        ret[r] += Vector4<T>(-s * scaled_row);
      }
    }
  }
  for (int k = 3; k >= 0; --k)
  {
    const Pair &p = swaped_pairs[k];
    ret.SwapColumns(p.first, p.second);
  }

  return ret;
}
template auto Inverse(const Matrix4x4<Float>& m) -> Matrix4x4<Float>;
template auto Inverse(const Matrix4x4<int>& m)   -> Matrix4x4<int>;

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  return Matrix4x4<T>(m[0][0], m[1][0], m[2][0], m[3][0],
                      m[0][1], m[1][1], m[2][1], m[3][1],
                      m[0][2], m[1][2], m[2][2], m[3][2],
                      m[0][3], m[1][3], m[2][3], m[3][3]);
}
template auto Transpose(const Matrix4x4<Float>& m) -> Matrix4x4<Float>;
template auto Transpose(const Matrix4x4<int>& m)   -> Matrix4x4<int>;

} // namespace niecpe
