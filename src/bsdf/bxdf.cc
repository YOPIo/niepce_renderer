/*!
 * @file bsdf.cc
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
Bxdf::Bxdf (const Intersection& intersection) :
  normal_ (intersection.Normal ())
{
  // Build orthonormal basis.
  BuildOrthonormalBasis (normal_, &tangent_, &binormal_);
}
/*
// ---------------------------------------------------------------------------
*/
/*!
 * @namespace bsdf
 * @brief 
 * @details 
 */
namespace bsdf
{
/*
// ---------------------------------------------------------------------------
*/
auto Dot (const Vector3f& v) -> Float
{
  return v.Y ();
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
