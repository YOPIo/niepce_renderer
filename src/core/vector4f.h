#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "algebra.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct alignas (16) Vector4f final
{
public:
  /* Constructors */
  Vector4f ();
  Vector4f (Float x, Float y , Float z, Float w);
  explicit Vector4f (Float s);

  ~Vector4f () = default;

  Vector4f (const Vector4f&  v) = default;
  Vector4f (      Vector4f&& v) = default;

  /* Operators */
  auto operator = (const Vector4f&  v) -> Vector4f& = default;
  auto operator = (      Vector4f&& v) -> Vector4f& = default;

  auto operator [] (unsigned idx) const -> Float;
  auto operator [] (unsigned idx)       -> Float&;

  /* Getter */
  auto X () const -> Float;
  auto Y () const -> Float;
  auto Z () const -> Float;
  auto W () const -> Float;

  /* Setter */
  auto SetX (Float x) -> void;
  auto SetY (Float y) -> void;
  auto SetZ (Float z) -> void;
  auto SetW (Float w) -> void;

  /* Methods */
  auto At (unsigned idx) const -> Float;
  auto At (unsigned idx)       -> Float&;

  auto Normalize  ()       -> Vector4f&;
  auto Normalized () const -> Vector4f;

  auto Length ()        const -> Float;
  auto LengthSquared () const -> Float;

  // Check status
  auto HasNaN       () const -> bool;
  auto IsNormalized () const -> bool;

  auto ToString () const -> std::string;

  /* Constant values */
  static constexpr auto Max      () -> Vector4f;
  static constexpr auto Min      () -> Vector4f;
  static constexpr auto Infinity () -> Vector4f;
  static constexpr auto Lowest   () -> Vector4f;
  static constexpr auto One      () -> Vector4f;
  static constexpr auto Zero     () -> Vector4f;


  /* Vector4f private data */
private:
  union
  {
    std::array <Float, 4> xyzw_;
    std::array <Float, 4> rgba_;
    struct { Float x_, y_, z_, w_; };
    struct { Float r_, g_, b_, a_; };
  };

}; // struct Vector4f
/*
// ---------------------------------------------------------------------------
// Global operators for Vector4f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector4f& lhs, const Vector4f& rhs) -> bool;
auto operator != (const Vector4f& lhs, const Vector4f& rhs) -> bool;

auto operator - (const Vector4f& v) -> Vector4f;

auto operator + (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f;
auto operator - (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f;
auto operator * (Float t, const Vector4f& v) -> Vector4f;
auto operator * (const Vector4f& v, Float t) -> Vector4f;
auto operator / (const Vector4f& v, Float t) -> Vector4f;
/*
// ---------------------------------------------------------------------------
// Global functions for Vector4f
// ---------------------------------------------------------------------------
*/
auto Multiply (const Vector4f& lhs, const Vector4f& rhs) -> Vector4f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "vector4f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR3F_H_
