#ifndef _VECTOR2F_H_
#define _VECTOR2F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "algebra.h"
/*
// ---------------------------------------------------------------------------
// TODO: Support SIMD
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct alignas(16) Vector2f final
{
public:
  /* Constructors */
  Vector2f ();
  Vector2f (Float x, Float y);
  explicit Vector2f (Float s);

  ~Vector2f () = default;

  Vector2f (const Vector2f&  p) = default;
  Vector2f (      Vector2f&& p) = default;


  /* Operators */
  auto operator = (const Vector2f&  p) -> Vector2f& = default;
  auto operator = (      Vector2f&& p) -> Vector2f& = default;

  auto operator [] (unsigned idx) const -> Float;
  auto operator [] (unsigned idx)       -> Float&;

  /* Getter */
  auto X () const -> Float;
  auto Y () const -> Float;

  /* Setter */
  auto SetX (Float x) -> void;
  auto SetY (Float y) -> void;


  /* Methods */
  auto At (unsigned idx) const -> Float;
  auto At (unsigned idx)       -> Float&;

  auto Normalize  ()       -> Vector2f&;
  auto Normalized () const -> Vector2f;

  auto Length        () const -> Float;
  auto LengthSquared () const -> Float;

  // Check status
  auto HasNaN       () const -> bool;
  auto IsNormalized () const -> bool;

  auto ToString () const -> std::string;


  /* Constant values */
  static constexpr auto Max      () -> Vector2f;
  static constexpr auto Min      () -> Vector2f;
  static constexpr auto Infinity () -> Vector2f;
  static constexpr auto Lowest   () -> Vector2f;
  static constexpr auto One      () -> Vector2f;
  static constexpr auto Zero     () -> Vector2f;


  /* Vector2f private data */
private:
  union
  {
    std::array <Float, 2> xy_;
    std::array <Float, 2> uv_;
    std::array <Float, 2> st_;
    struct { Float x_, y_; };
    struct { Float u_, v_; };
    struct { Float s_, t_; };
  };
}; // struct Vector2f
/*
// ---------------------------------------------------------------------------
// Vector2f global operators
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector2f& lhs, const Vector2f& rhs) -> bool;
auto operator != (const Vector2f& lhs, const Vector2f& rhs) -> bool;

auto operator -  (const Vector2f& v) -> Vector2f;

auto operator +  (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
auto operator -  (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
auto operator *  (const Vector2f& v, Float t) -> Vector2f;
auto operator *  (Float t, const Vector2f& v) -> Vector2f;
auto operator /  (const Vector2f& v, Float t) -> Vector2f;
/*
// ---------------------------------------------------------------------------
// Vector2f global functions
// ---------------------------------------------------------------------------
*/
auto Dot      (const Vector2f& lhs, const Vector2f& rhs) -> Float;
auto Cross    (const Vector2f& lhs, const Vector2f& rhs) -> Float;
auto Multiply (const Vector2f& lhs, const Vector2f& rhs) -> Vector2f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "vector2f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR2F_H_
