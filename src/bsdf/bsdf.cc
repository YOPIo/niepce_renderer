/*!
 * @file bsdfs.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bsdf.h"
#include "bsdf_record.h"
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
Bsdf::Bsdf (const Intersection &isect) :
  isect_ (isect),
  Bxdf (niepce::Bxdf::Type::kUnknown)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Sample (BsdfRecord *record, const Point2f &sample)
  const noexcept -> Spectrum
{
  // ---------------------------------------------------------------------------
  // Ready for sample.
  // ---------------------------------------------------------------------------
  // Get the type of sampleing bsdf type.
  const auto &type = record->SamplingTarget ();

  // Transform outgoing direction in world space into bsdf space and store it.
  const auto &wwo = record->Outgoing (bsdf::Coordinate::kWorld);
  record->SetOutgoing (WorldToLocal (wwo), bsdf::Coordinate::kLocal);

  const auto num_bxdf = bxdfs_.size ();
  if (num_bxdf == 0)
  {
    // Handle case, no BxDFs are stored.
    record->SetPdf (0);
    record->SetBsdf (Spectrum (0));
    record->SetCosWeight (0);
    record->SetSampledBsdfType (niepce::Bxdf::Type::kUnknown);
    return Spectrum (0);
  }

  // ---------------------------------------------------------------------------
  // Choose BxDF randomly to sample the incident.
  // ---------------------------------------------------------------------------
  auto idx = std::min (static_cast <std::size_t> (sample[0] * num_bxdf),
                       num_bxdf - 1);
  Bxdf* bxdf = nullptr;
  for (int i = 0; i < num_bxdf; ++i)
  {
    if (bxdfs_[i]->FulFill (type) && idx-- == 0)
    {
      bxdf = bxdfs_[i];
      break;
    }
  }
  if (bxdf == nullptr)
  {
    record->SetPdf (0);
    record->SetBsdf (Spectrum (0));
    record->SetCosWeight (0);
    record->SetSampledBsdfType (niepce::Bxdf::Type::kUnknown);
    return Spectrum (0);
  }

  // ---------------------------------------------------------------------------
  // Sample the incident direction, pdf, bsdf and cos weight from chosen BxDF.
  // ---------------------------------------------------------------------------
  // Sample the incident direction.
  const auto f = bxdf->Sample (record, sample);
  const auto wi  = record->Incident (bsdf::Coordinate::kLocal);
  const auto wwi = LocalToWorld (wi);
  record->SetIncident (wwi, bsdf::Coordinate::kWorld);

  // Compute the pdf.
  const auto pdf = Pdf (*record);
  record->SetPdf (pdf);

  // Compute the evaluated bsdf.
  const auto bsdf = Evaluate (*record);
  record->SetBsdf (bsdf);

  // Compute the cos weight.
  const auto weight = std::fabs (Dot (wwi, isect_.Normal ()));
  record->SetCosWeight (weight);

  return bsdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Evaluate (const BsdfRecord &record) const noexcept -> Spectrum
{
  // Get outgoing and incident directions in bsdf space.
  const auto &wo = record.Outgoing (bsdf::Coordinate::kLocal);
  const auto &wi = record.Incident (bsdf::Coordinate::kWorld);

  // Handle case
  if (wo.Z () == 0) { return Spectrum (0); }

  // Get outgoing, incident directions and shading normal in world space.
  const auto &wwo = record.Outgoing (bsdf::Coordinate::kWorld);
  const auto &wwi = record.Incident (bsdf::Coordinate::kWorld);
  const auto &n = isect_.Normal ();

  // Confirm reflection or refraction.
  bool reflect = Dot (wwo, n) * Dot (wwi, n) > 0;

  // Get the type of BSDF sampling target.
  const auto &sampling_type = record.SamplingTarget ();

  // Loop for bxdfs in this class.
  Spectrum f (0);
  for (const auto & bxdf : bxdfs_)
  {
    bool require = (reflect && (this->type_ & niepce::Bxdf::Type::kReflection))
                || (!reflect && (this->type_ & niepce::Bxdf::Type::kTransmittion));
    if (require && bxdf->FulFill (sampling_type))
    {
      f = f + bxdf->Evaluate (record);
    }
  }
  return f;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::Pdf (const BsdfRecord &record) const noexcept -> Float
{
  // If no bxdf in this class, return 0.
  if (bxdfs_.empty ()) { return 0.0; }

  // Get outgoing and incident directions in bsdf space.
  const auto &wo = record.Outgoing (bsdf::Coordinate::kLocal);
  const auto &wi = record.Incident (bsdf::Coordinate::kLocal);

  // Handle case, ray parallel to delta surface.
  if (wo.Z () == 0) { return 0.0; }

  // Get the type of sampling bsdf type.
  const auto &type = record.SamplingTarget ();

  // Compute the pdf. (Sum of all BxDF)
  Float pdf = 0;
  int   num_sampled = 0;
  for (const auto &bxdf : bxdfs_)
  {
    if (bxdf->FulFill (type))
    {
      pdf += bxdf->Pdf (record);
      ++num_sampled;
    }
  }

  return num_sampled > 0 ? pdf / num_sampled : 0.0;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::AddBxdf (Bxdf *bxdf) noexcept -> void
{
  // bxdfs_.push_back (std::move (bxdf));
  bxdfs_.push_back (bxdf);

  // Update the type of BSDF.
  this->type_ = niepce::Bxdf::Type (this->type_ | bxdf->BsdfType ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::WorldToLocal (const Vector3f &v) const noexcept -> Vector3f
{
  return Vector3f (Dot (v, isect_.Tangent ()),
                   Dot (v, isect_.Binormal ()),
                   Dot (v, isect_.Normal ()));
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::LocalToWorld (const Vector3f &v) const noexcept -> Vector3f
{
  const auto &n = isect_.Normal ();
  const auto &s = isect_.Tangent ();
  const auto &t = isect_.Binormal ();
  return Vector3f (v.X () * s.X () + v.Y () * t.X () + v.Z () * n.X (),
                   v.X () * s.Y () + v.Y () * t.Y () + v.Z () * n.Y (),
                   v.X () * s.Z () + v.Y () * t.Z () + v.Z () * n.Z ());
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
