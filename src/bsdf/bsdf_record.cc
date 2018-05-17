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
auto BsdfRecord::Incident (CoordinateSystem cs) const noexcept -> Vector3f
{
  if (cs == kWorld)
  {
    // Return the outgoing direction in world coordinates.
    return intersection_.ToWorld (incident_);
  }
  // Return the incident direction in BSDF coordinates.
  return incident_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Outgoing (CoordinateSystem cs) const noexcept -> Vector3f
{
  if (cs == kWorld)
  {
    // Return the outgoing direction in world coordinates.
    return intersection_.ToWorld (outgoing_);
  }
  // Return the outgoing direction in BSDF coordinates.
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
