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
{}
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
auto BsdfRecord::Incident () const noexcept -> Vector3f
{
  return world_incident_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Outgoing () const noexcept -> Vector3f
{
  return world_outgoing_;
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
auto BsdfRecord::SetBsdfValue (const Vector3f& basf_value) noexcept -> void
{
  this->bsdf_ = basf_value;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetIncident (const Vector3f& incident) noexcept -> void
{
  this->world_incident_ = incident;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetOutgoing (const Vector3f& outgoing) noexcept -> void
{
  this->world_outgoing_ = outgoing;
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
