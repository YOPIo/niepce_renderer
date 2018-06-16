#ifndef _VECTOR3F_H_
#define _VECTOR3F_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "point3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class Vector3f
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
  auto X () const noexcept -> Float;
  auto Y () const noexcept -> Float;
  auto Z () const noexcept -> Float;

  /* Setter */
  auto SetX (Float x) noexcept -> void;
  auto SetY (Float y) noexcept -> void;
  auto SetZ (Float z) noexcept -> void;

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
  static auto Max      () noexcept -> Vector3f;
  static auto Min      () noexcept -> Vector3f;
  static auto Infinity () noexcept -> Vector3f;
  static auto Lowest   () noexcept -> Vector3f;
  static auto One      () noexcept -> Vector3f;
  static auto Zero     () noexcept -> Vector3f;

  /* Vector3f private data */
private:
  union
  {
    std::array <Float, 3> xyz_;
    std::array <Float, 3> rgb_;
    struct { Float x_, y_, z_; };
    struct { Float r_, g_, b_; };
  };

}; // class Vector3f
/*
// ---------------------------------------------------------------------------
// Global operators for Vector3f
// ---------------------------------------------------------------------------
*/
auto operator == (const Vector3f& lhs, const Vector3f& rhs) -> bool;
auto operator != (const Vector3f& lhs, const Vector3f& rhs) -> bool;
/*
// ---------------------------------------------------------------------------
*/
auto operator - (const Vector3f& v) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
auto operator + (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator + (const Vector3f& lhs, const Point3f&  rhs) -> Point3f;
auto operator + (const Point3f&  lhs, const Vector3f& rhs) -> Point3f;
auto operator - (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator * (Float t, const Vector3f& v) -> Vector3f;
auto operator * (const Vector3f& v, Float t) -> Vector3f;
auto operator / (const Vector3f& v, Float t) -> Vector3f;
/*
// ---------------------------------------------------------------------------
*/
auto operator * (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto operator / (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
/*
// ---------------------------------------------------------------------------
// Global functions for Vector3f
// ---------------------------------------------------------------------------
*/
auto Dot       (const Vector3f& lhs, const Vector3f& rhs) -> Float;
auto Cross     (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto Multiply  (const Vector3f& lhs, const Vector3f& rhs) -> Vector3f;
auto Normalize (const Vector3f& vec) -> Vector3f;
auto BuildOrthonormalBasis
(
 const Vector3f& normal,
 Vector3f* binormal,
 Vector3f* tangent
)
  -> void;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VECTOR3F_H_
