/*!
 * @file lambert.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "lambert.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Pdf (const BxdfRecord& record)
  const noexcept -> Float
{
  //! Lambert PDF : $ cos\theta / \pi $
  return bxdf::Dot (record.Incident ()) / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Evaluate (const BxdfRecord& record) const noexcept -> Vector3f
{
  //! Lambert BRDF : $ \rho / \pi $
  return 
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

