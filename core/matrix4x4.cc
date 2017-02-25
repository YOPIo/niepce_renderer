#include "matrix4x4.h"

namespace niepce
{

// todo: implementation
template <typename T>
auto Inverse(const Matrix4x4<T>& m) -> Matrix4x4<T>;

template <typename T>
auto Transpose(const Matrix4x4<T>& m) -> Matrix4x4<T>
{
  return Matrix4x4<T>(m[0][0], m[1][0], m[2][0], m[3][0],
                      m[0][1], m[1][1], m[2][1], m[3][1],
                      m[0][2], m[1][2], m[2][2], m[3][2],
                      m[0][3], m[1][3], m[2][3], m[3][3]);
}

} // namespace niecpe
