/*
// ---------------------------------------------------------------------------
// Column-major matrix4x4
// ---------------------------------------------------------------------------
*/
#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------
*/
auto Identity ()                     -> Matrix4x4;
auto Inverse  (const Matrix4x4& mat) -> Matrix4x4;
/*
// ---------------------------------------------------------------------------
// Class declarations
// ---------------------------------------------------------------------------
*/
struct Matrix4x4
{
  Matrix4x4 ();
  Matrix4x4 (Float m);
  Matrix4x4 (Float m00, Float m01, Float m02, Float m03,
             Float m10, Float m11, Float m12, Float m13,
             Float m20, Float m21, Float m22, Float m23,
             Float m30, Float m31, Float m32, Float m33);
  virtual ~Matrix4x4 () = default;

  Matrix4x4 (const Matrix4x4&  mat) = default;
  Matrix4x4 (      Matrix4x4&& mat) = default;

  auto operator = (const Matrix4x4&  mat) -> Matrix4x4& = default;
  auto operator = (      Matrix4x4&& mat) -> Matrix4x4& = default;


  /* Matrix4x4 public operators */
 public:
  auto operator () (Index row, Index col) const -> Float;
  auto operator () (Index row, Index col)       -> Float&;

  auto operator += (const Matrix4x4& mat) -> Matrix4x4&;
  auto operator -= (const Matrix4x4& mat) -> Matrix4x4&;
  auto operator *= (const Matrix4x4& mat) -> Matrix4x4&;
  auto operator *= (Float scale)          -> Matrix4x4&;


  /* Matrix4x4 public methods */
 public:
  auto HasNaN () const -> bool;


  /* Matrix4x4 public constexpr */
 public:
  static constexpr uint32_t kNumElementsMat4 = 16;

  /* Matrix4x4 public data */
 public:
  union
  {
    std::array <Float, kNumElementsMat4> elements;
    struct
    {
      struct { Float m00, m10, m20, m30; };
      struct { Float m01, m11, m21, m31; };
      struct { Float m02, m12, m22, m32; };
      struct { Float m03, m13, m23, m33; };
    };
  };
}; // struct Matrix4x4
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "matrix4x4.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATRIX4X4_H_
