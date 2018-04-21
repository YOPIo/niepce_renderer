#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct alignas (16) Vector3f final
{
public:
  /* Constructors */
  Vector3f ();
  Vector3f (Float x, Float y , Float z);
  explicit Vector3f (Float s);

  ~Vector3f () = default;

  Vector3f (const Vector3f&  v) = default;
  Vector3f (      Vector3f&& v) = default;

  /* Operators */
  auto operator = (const Vector3f&  v) -> Vector3f& = default;
  auto operator = (      Vector3f&& v) -> Vector3f& = default;

  auto operator [] (unsigned idx) const -> Float;
  auto operator [] (unsigned idx)       -> Float&;

  /* Getter */
  auto X () const -> Float;
  auto Y () const -> Float;
  auto Z () const -> Float;

  /* Setter */
  auto SetX (Float x) -> void;
  auto SetY (Float y) -> void;
  auto SetZ (Float z) -> void;

  /* Methods */
  auto At (unsigned idx) const -> Float;
  auto At (unsigned idx)       -> Float&;

  auto Normalize  ()       -> Vector3f&;
  auto Normalized () const -> Vector3f;

  auto Length ()        const -> Float;
  auto LengthSquared () const -> Float;

  // Check status
  auto HasNaN       () const -> bool;
  auto IsNormalized () const -> bool;

  auto ToString () const -> std::string;

  /* Constant values */
  static constexpr auto Max      () -> Vector3f;
  static constexpr auto Min      () -> Vector3f;
  static constexpr auto Infinity () -> Vector3f;
  static constexpr auto Lowest   () -> Vector3f;
  static constexpr auto One      () -> Vector3f;
  static constexpr auto Zero     () -> Vector3f;


  /* Vector3f private data */
private:
  union
  {
    std::array <Float, 3> xyz_;
    std::array <Float, 3> rgb_;
    struct { Float x_, y_, z_; };
    struct { Float r_, g_, b_; };
  };

}; // struct Vector3f
/*
// ---------------------------------------------------------------------------
// Global operators for Vector3f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector3f& lhs, const Vector3f& rhs) -> bool;
auto operator != (const Vector3f& lhs, const Vector3f& rhs) -> bool;

auto operator - (const Vector3f& v) -> Vector3f;

auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator * (Float t, const Vector3f& v) -> Vector3f;
auto operator * (const Vector3f& v, Float t) -> Vector3f;
auto operator / (const Vector3f& v, Float t) -> Vector3f;
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
auto Dot      (const Vector3f& lhs, const Vector3f& rhs) -> Float;
auto Cross    (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto Multiply (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#include "vector3f.inl"
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR3F_H_
