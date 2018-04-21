#ifndef _MATRIX4X4_H_
#define _MATRIX4X4_H_
/*
// ---------------------------------------------------------------------------
*/
#include "algebra.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct Vector3f;
struct Vector4f;
/*
// ---------------------------------------------------------------------------
// Forward declarations
// ---------------------------------------------------------------------------
*/
auto Inverse  (const Matrix4x4f& mat) -> Matrix4x4f;
/*
// ---------------------------------------------------------------------------
// Class declarations
// ---------------------------------------------------------------------------
*/
struct alignas (32) Matrix4x4f final
{
public:
  Matrix4x4f ();
  Matrix4x4f (Float m);
  Matrix4x4f (Float m00, Float m01, Float m02, Float m03,
              Float m10, Float m11, Float m12, Float m13,
              Float m20, Float m21, Float m22, Float m23,
              Float m30, Float m31, Float m32, Float m33);
  ~Matrix4x4f () = default;

  Matrix4x4f (const Matrix4x4f&  mat) = default;
  Matrix4x4f (      Matrix4x4f&& mat) = default;

  auto operator = (const Matrix4x4f&  mat) -> Matrix4x4f& = default;
  auto operator = (      Matrix4x4f&& mat) -> Matrix4x4f& = default;


  /* Operators */
public:
  auto operator () (unsigned row, unsigned col) const -> Float;
  auto operator () (unsigned row, unsigned col)       -> Float&;

  auto operator += (const Matrix4x4f& mat) -> Matrix4x4f&;
  auto operator -= (const Matrix4x4f& mat) -> Matrix4x4f&;
  auto operator *= (const Matrix4x4f& mat) -> Matrix4x4f&;
  auto operator *= (Float scale)           -> Matrix4x4f&;

  /* Methods */
public:
  auto HasNaN () const -> bool;


  /* Constant value */
public:
  static constexpr auto Identity () -> Matrix4x4f;
  static constexpr auto Zero     () -> Matrix4x4f;


  /* Private data */
private:
  union
  {
    std::array <Float, 16> elements;
    struct
    {
      struct { Float m00, m10, m20, m30; };
      struct { Float m01, m11, m21, m31; };
      struct { Float m02, m12, m22, m32; };
      struct { Float m03, m13, m23, m33; };
    };
  };
}; // struct Matrix4x4f
/*
// ---------------------------------------------------------------------------
// Global operator for Matrix4x4f
// ---------------------------------------------------------------------------
*/
auto operator == (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool;
auto operator != (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> bool;

auto operator + (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> Matrix4x4f;
auto operator - (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> Matrix4x4f;
auto operator * (const Matrix4x4f& lhs, const Matrix4x4f& rhs) -> Matrix4x4f;

auto operator * (const Matrix4x4f& mat, const Vector3f& v) -> Vector3f;
auto operator * (const Matrix4x4f& mat, const Vector4f& v) -> Vector4f;
auto operator * (const Matrix4x4f& mat, Float scale) -> Matrix4x4f;
auto operator * (Float scale, const Matrix4x4f& mat) -> Matrix4x4f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "matrix4x4f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATRIX4X4_H_
