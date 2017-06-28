#include "matrix4x4.h"

namespace niepce
{

auto Inverse (const Matrix4x4& m) -> Matrix4x4
{
  std::array<int, 4> indxc;
  std::array<int, 4> indxr;
  std::array<int, 4> ipiv = {0, 0, 0, 0};
  std::array<std::array<Float, 4>, 4> minv;
  std::memcpy(minv.begin(), m.matrix.begin(), 4 * 4 * sizeof(Float));

  for (int i = 0; i < 4; i++)
  {
    int irow = 0, icol = 0;
    Float big = 0.f;
    for (int j = 0; j < 4; j++)
    {
      if (ipiv[j] != 1)
      {
        for (int k = 0; k < 4; k++)
        {
          if (ipiv[k] == 0)
          {
            if (std::abs (minv[j][k]) >= big)
            {
              big = static_cast<Float>(std::abs(minv[j][k]));
              irow = j;
              icol = k;
            }
          }
          if (ipiv[k] > 1)
          {
            std::cerr << "Inverse matrix error" << std::endl;
            // Error
          }
        }
      }
    }
    ++ipiv[icol];

    if (irow != icol) {
      for (int k = 0; k < 4; ++k) std::swap (minv[irow][k], minv[icol][k]);
    }
    indxr[i] = irow;
    indxc[i] = icol;
    if (minv[icol][icol] == 0.f)
    {
      std::cerr << "Inverse matrix error" << std::endl;
      // Error
    }


    Float pivinv = 1. / minv[icol][icol];
    minv[icol][icol] = 1.;
    for (int j = 0; j < 4; j++) { minv[icol][j] *= pivinv; }

    for (int j = 0; j < 4; j++)
    {
      if (j != icol)
      {
        Float save = minv[j][icol];
        minv[j][icol] = 0;
        for (int k = 0; k < 4; k++) { minv[j][k] -= minv[icol][k] * save; }
      }
    }
  }

  for (int j = 3; j >= 0; j--)
  {
    if (indxr[j] != indxc[j])
    {
      for (int k = 0; k < 4; k++)
        std::swap(minv[k][indxr[j]], minv[k][indxc[j]]);
    }
  }

  return Matrix4x4 (minv[0][0], minv[0][1], minv[0][2], minv[0][3],
                    minv[1][0], minv[1][1], minv[1][2], minv[1][3],
                    minv[2][0], minv[2][1], minv[2][2], minv[2][3],
                    minv[3][0], minv[3][1], minv[3][2], minv[3][3]);
}


auto Transpose (const Matrix4x4& m) -> Matrix4x4
{
  return Matrix4x4 (m (0, 0), m (1, 0), m (2, 0), m (3, 0),
                    m (0, 1), m (1, 1), m (2, 1), m (3, 1),
                    m (0, 2), m (1, 2), m (2, 2), m (3, 2),
                    m (0, 3), m (1, 3), m (2, 3), m (3, 3));
}

} // namespace niecpe
