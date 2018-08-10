/*!
 * @file bsdf_record.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bsdf_record.h"
#include "../core/intersection.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
BsdfRecord::BsdfRecord (const Intersection& intersection) :
  intersection_ (intersection),
  world_outgoing_ (intersection.Outgoing ())
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
auto BsdfRecord::CosWeight () const noexcept -> Float
{
  return cos_t_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Incident (bsdf::Coordinate coordinate) const noexcept -> Vector3f
{
  if (coordinate == niepce::bsdf::Coordinate::kLocal)
  {
    return local_incident_;
  }
  return world_incident_;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::Outgoing (bsdf::Coordinate coordinate) const noexcept -> Vector3f
{
  if (coordinate == niepce::bsdf::Coordinate::kLocal)
  {
    return local_outgoing_;
  }
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
auto BsdfRecord::SamplingTarget () const noexcept -> niepce::Bxdf::Type
{
  return target_type_;
}
auto BsdfRecord::SampledType () const noexcept -> niepce::Bxdf::Type
{
  return sampled_type_;
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
auto BsdfRecord::SetCosWeight (Float cos_theta) noexcept -> void
{
  this->cos_t_ = cos_theta;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetIncident
(
 const Vector3f   &incident,
 bsdf::Coordinate coordinate
)
  noexcept -> void
{
  if (coordinate == niepce::bsdf::Coordinate::kLocal)
  {
    local_incident_ = incident;
    return ;
  }
  world_incident_ = incident;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetOutgoing
(
 const Vector3f   &outgoing,
 bsdf::Coordinate coordinate
)
  noexcept -> void
{
  if (coordinate == niepce::bsdf::Coordinate::kLocal)
  {
    local_outgoing_ = outgoing;
    return ;
  }
  world_outgoing_ = outgoing;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetPdf (Float pdf) noexcept -> void
{
  pdf_ = pdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetSamplingTarget (niepce::Bxdf::Type type) noexcept -> void
{
  target_type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
auto BsdfRecord::SetSampledBsdfType (niepce::Bxdf::Type type) noexcept -> void
{
  sampled_type_ = type;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
