/*!
 * @file bxdf.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bxdf.h"
#include "../core/intersection.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Bxdf::Bxdf (niepce::Bxdf::Type type) :
  type_ (type)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Bxdf::FulFill (niepce::Bxdf::Type type) const noexcept -> bool
{
  return ((type_ & type) == type_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bxdf::BsdfType () const noexcept -> niepce::Bxdf::Type
{
  return type_;
}
/*
// ---------------------------------------------------------------------------
*/
namespace bsdf
{
/*
// ---------------------------------------------------------------------------
*/
auto CosTheta (const Vector3f& w) -> Float
{
  return w.Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto Cos2Theta (const Vector3f& w) -> Float
{
  return w.Z () * w.Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsCosTheta (const Vector3f& w) -> Float
{
  return std::abs (w.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
auto SinTheta (const Vector3f& w) -> Float
{
  return std::sqrt (Sin2Theta (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto Sin2Theta (const Vector3f& w) -> Float
{
  return std::fmax (0.0, 1.0 - Cos2Theta (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsSinTheta (const Vector3f& w) -> Float
{
  return SinTheta (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto TanTheta (const Vector3f& w) -> Float
{
  return SinTheta (w) / CosTheta (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto Tan2Theta (const Vector3f& w) -> Float
{
  return Sin2Theta(w) / Cos2Theta(w);
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsTanTheta (const Vector3f& w) -> Float
{
  return std::abs (TanTheta (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto CosPhi (const Vector3f& w) -> Float
{
  const Float sin_theta = SinTheta (w);
  return (sin_theta == 0) ? 1 : Clamp (w.Z () / sin_theta,
                                       static_cast <Float> (-1.0),
                                       static_cast <Float> (1.0));
}
/*
// ---------------------------------------------------------------------------
*/
auto Cos2Phi (const Vector3f& w) -> Float
{
  return CosPhi (w) * CosPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsCosPhi (const Vector3f& w) -> Float
{
  return std::fabs (CosPhi (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto SinPhi (const Vector3f& w) -> Float
{
  const Float sin_theta = SinTheta (w);
  return (sin_theta == 0) ? 0 : Clamp (w.Y () / sin_theta,
                                       static_cast <Float> (-1.0),
                                       static_cast <Float> (1.0));
}
/*
// ---------------------------------------------------------------------------
*/
auto Sin2Phi (const Vector3f& w) -> Float
{
  return SinPhi (w) * SinPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsSinPhi (const Vector3f& w) -> Float
{
  return std::fabs (SinPhi (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto TanPhi (const Vector3f& w) -> Float
{
  return SinPhi (w) / CosPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto Tan2Phi (const Vector3f& w) -> Float
{
  return TanPhi (w) * TanPhi (w);
}
/*
// ---------------------------------------------------------------------------
*/
auto AbsTanPhi (const Vector3f& w) -> Float
{
  return std::fabs (TanPhi (w));
}
/*
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector3f& v) -> Float
{
  return v.Z ();
}
/*
// ---------------------------------------------------------------------------
*/
auto HasSameHemisphere (const Vector3f& lhs, const Vector3f& rhs) -> bool
{
  return lhs.Z () * rhs.Z () > 0;
}
/*
// ---------------------------------------------------------------------------
*/
auto Reflect (const Vector3f& v, const Vector3f& normal) -> Vector3f
{
  return -v + 2.0 * Dot (v, normal) * normal;
}
/*
// ---------------------------------------------------------------------------
*/
auto Refract
(
 const Vector3f& in,
 const Vector3f& normal,
 Float ior1,
 Float ior2,
 Vector3f* refract
)
  -> bool
{
  const Float ior = ior1 / ior2;

  // Compute $ cos(\theta) $ using Snells's law.
  const Float cos_theta1  = Dot (normal, in);
  const Float sin2_theta1 = std::fmax (0.0, (1.0 - cos_theta1 * cos_theta1));
  const Float sin2_theta2 = ior * ior * sin2_theta2;

  if (sin2_theta2 >= 1)
  {
    // Total reflection
    return false;
      // return Reflect (in, normal);
  }

  const Float cos_theta2 = std::sqrt (1.0 - sin2_theta2);

  *refract = ior * -in + (ior * cos_theta1 - cos_theta2) * normal;

  return true;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
