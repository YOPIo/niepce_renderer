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
{
  // TODO: Delete
  // Override the normal, tangent and binormal if shading normal present.
  if (isect_.HasShadingNormal ())
  {
    isect_.SetNormal (isect_.ShadingNormal ());
  }
}
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
  const auto num_comp = NumMatchingComponent (type);

  if (num_comp == 0)
  {
    // There is no component to evaluate the BxDF.
    record->SetPdf (0.0);
    record->SetBsdf (Spectrum (0));
    record->SetSampledBsdfType (niepce::Bxdf::Type::kUnknown);
    return Spectrum (0);
  }

  // Transform outgoing direction in world space into bsdf space and store it.
  const auto &wwo = record->Outgoing (bsdf::Coordinate::kWorld);
  record->SetOutgoing (WorldToLocal (wwo), bsdf::Coordinate::kLocal);

  // ---------------------------------------------------------------------------
  // Choose BxDF randomly to sample the incident.
  // ---------------------------------------------------------------------------
  auto idx = std::min (static_cast <std::size_t> (sample[0] * num_comp),
                       static_cast <std::size_t> (num_comp - 1));
  Bxdf* bxdf = nullptr;
  auto cnt = idx;
  for (int i = 0; i < num_comp; ++i)
  {
    if (bxdfs_[i]->FulFill (type) && cnt-- == 0)
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

  // Remaping sample[0] since it was used.
  auto resample = Point2f (Clamp (sample[0] * num_comp - idx), sample[1]);

  // ---------------------------------------------------------------------------
  // Sample the incident direction, pdf, bsdf and cos weight from chosen BxDF.
  // ---------------------------------------------------------------------------
  // Sample the incident direction.
  auto f = bxdf->Sample (record, resample);
  const auto wi  = record->Incident (bsdf::Coordinate::kLocal);
  const auto wwi = LocalToWorld (wi);
  record->SetIncident (wwi, bsdf::Coordinate::kWorld);

  if (record->Pdf () == 0)
  {
    // Error case.
    record->SetPdf (0);
    record->SetBsdf (Spectrum (0));
    record->SetCosWeight (0);
    record->SetSampledBsdfType (niepce::Bxdf::Type::kUnknown);
    return Spectrum (0);
  }

  // Compute the pdf.
  if (!(bxdf->BsdfType () & Bxdf::Type::kSpecular) && num_comp > 1)
  {
    auto pdf = record->Pdf ();
    // pdf = Pdf (*record);
    for (int i = 0; i < bxdfs_.size (); ++i)
    {
      if (bxdfs_[i] != bxdf && bxdfs_[i]->FulFill (type))
      {
        pdf += bxdfs_[i]->Pdf (*record);
      }
    }
    if (num_comp > 1) { pdf /= num_comp; }
    record->SetPdf (pdf);
  }

  // Compute the evaluated bsdf.
  if (!(bxdf->BsdfType () & Bxdf::Type::kSpecular) && num_comp > 1)
  {
    f = Evaluate (*record);
    /*
    const auto &wwo = record->Outgoing (bsdf::Coordinate::kWorld);
    const auto &wwi = record->Incident (bsdf::Coordinate::kWorld);
    bool reflect = Dot (wwo, isect_.Normal ()) * Dot (wwi, isect_.Normal ()) > 0;
    for (int i = 0; i < bxdfs_.size (); ++i)
    {
      if (bxdfs_[i]->FulFill (type) &&
          ( reflect && (bxdfs_[i]->BsdfType () & Bsdf::Type::kReflection)) &&
          (!reflect && (bxdfs_[i]->BsdfType () & Bsdf::Type::kTransmittion)))
      {
        f = f + bxdfs_[i]->Evaluate (*record);
      }
    }
    */
    record->SetBsdf (f);
  }

  // Compute the cos weight.
  // const auto weight = std::fabs (Dot (wwi, isect_.Normal ()));
  const auto weight = bsdf::AbsCosTheta (wi);
  record->SetCosWeight (weight);

  return f;
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
  const auto &n   = isect_.Normal ();

  // Confirm reflection or refraction.
  bool reflect = Dot (wwo, n) * Dot (wwi, n) > 0;

  // Get the type of BSDF sampling target.
  const auto &sampling_type = record.SamplingTarget ();

  // Loop for bxdfs in this class.
  Spectrum f (0);
  for (const auto &bxdf : bxdfs_)
  {
    bool require
      =  ( reflect && (bxdf->BsdfType () & niepce::Bxdf::Type::kReflection))
      || (!reflect && (bxdf->BsdfType () & niepce::Bxdf::Type::kTransmittion));
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
  if (num_sampled > 1)
  {
    pdf /= static_cast <Float> (num_sampled);
  }

  return pdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto Bsdf::AddBxdf (Bxdf *bxdf) noexcept -> void
{
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
auto Bsdf::NumMatchingComponent (Bsdf::Type type) const noexcept -> int
{
  int res = 0;
  for (const auto &bxdf : bxdfs_)
  {
    if (bxdf->FulFill (type)) { res++; }
  }
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
