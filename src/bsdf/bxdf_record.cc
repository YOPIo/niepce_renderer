/*!
 * @file bsdf_record.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bxdf_record.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
BxdfRecord::BxdfRecord (const Intersection& intersection) :
  intersection_ (intersection)
{
  // Ready to transform outgoing direction to BSDF coordinates.
  const Vector3f n = intersection.Normal ();
  const Vector3f s = intersection.Tangent ();
  const Vector3f t = intersection.Binormal ();
  const Vector3f outgoing = Normalize (intersection.Outgoing ());

  // From normal, tangent and binormal vectors, transform ray outgoing direction
  // to BSDF coordinates.
  this->outgoing_ = Vector3f (Dot (outgoing, t),
                              Dot (outgoing, n),
                              Dot (outgoing, s));
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::Bxdf () const noexcept -> Vector3f
{
  return bsdf_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::Incident () const noexcept -> Vector3f
{
  return incident_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::Outgoing () const noexcept -> Vector3f
{
  return outgoing_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::Pdf () const noexcept -> Float
{
  return pdf_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::SetBxdfValue (const Vector3f& basf_value) noexcept -> void
{
  this->bsdf_ = basf_value;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::SetIncident (const Vector3f& incident) noexcept -> void
{
  this->incident_ = incident;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::SetOutgoing (const Vector3f& outgoing) noexcept -> void
{
  this->outgoing_ = outgoing;
}
/*
// ---------------------------------------------------------------------------
*/
auto BxdfRecord::SetPdf (Float pdf) noexcept -> void
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
