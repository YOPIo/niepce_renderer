/*!
 * @file bsdf.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bsdf.h"
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
Bsdf::Bsdf (const Intersection& intersection) :
  normal_ (intersection.Normal ())
{
  BuildOrthonormalBasis (normal_, &tangent_, &binormal_);
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::ToLocal (const Vector3f& w) const noexcept -> Vector3f
{
  return Vector3f (Dot (w, tangent_),
                   Dot (w, binormal_),
                   Dot (w, normal_));
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::ToWorld (const Vector3f& w) const noexcept -> Vector3f
{
  return Vector3f
    (w.X () * tangent_.X () + w.Y () * binormal_.X () + w.Z () * normal_.X (),
     w.X () * tangent_.Y () + w.Y () * binormal_.Y () + w.Z () * normal_.Y (),
     w.X () * tangent_.Z () + w.Y () * binormal_.Z () + w.Z () * normal_.Z ());
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
  return (sin_theta == 0) ? 1 : Clamp (w.Z () / sin_theta, -1.0, 1.0);
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
  return (sin_theta == 0) ? 0 : Clamp (w.Y () / sin_theta, -1.0, 1.0);
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
}  // namespace bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
