/*!
 * @file bsdf_record.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bsdf_record.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
BsdfRecord::BsdfRecord (const Intersection& intersection) :
  intersection_ (intersection)
{
  // Ready to transform outgoing direction to BSDF coordinates.
  const Vector3f n = intersection.Normal ();
  const Vector3f s = intersection.Tangent ();
  const Vector3f t = intersection.Binormal ();
  const Vector3f outgoing = Normalize (intersection.Outgoing ());

  // From normal, tangent and binormal vectors, transform ray outgoing direction
  // to BSDF coordinates.
  this->outgoing_ = intersection_.ToLocal (outgoing);
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Bsdf () const noexcept -> Vector3f
{
  return bsdf_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::CosTheta () const noexcept -> Float
{
  return cos_t_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Incident () const noexcept -> Vector3f
{
  // Return the incident direction in BSDF coordinates.
  return incident_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Outgoing () const noexcept -> Vector3f
{
  return outgoing_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Pdf () const noexcept -> Float
{
  return pdf_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetBsdf (const Spectrum& basf_value) noexcept -> void
{
  this->bsdf_ = basf_value;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetCosTheta (Float cos_theta) noexcept -> void
{
  this->cos_t_ = cos_theta;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetIncident (const Vector3f& incident) noexcept -> void
{
  this->incident_ = incident;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetOutgoing (const Vector3f& outgoing) noexcept -> void
{
  this->outgoing_ = outgoing;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetPdf (Float pdf) noexcept -> void
{
  this->pdf_ = pdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
