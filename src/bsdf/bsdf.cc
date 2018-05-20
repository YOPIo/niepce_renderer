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
}  // namespace bsdf
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
