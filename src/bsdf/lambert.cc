/*!
 * @file lambert.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "lambert.h"
#include "bsdf.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Lambert::Lambert (const Spectrum& reflectance) :
  Bsdf (),
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Pdf (const BsdfRecord& record)
  const noexcept -> Float
{
  //! Lambert PDF : $ cos\theta / \pi $
  const Vector3f incident
    = record.Outgoing (BsdfRecord::CoordinateSystem::kBsdf);
  const Float pdf = bsdf::Dot (incident) / kPi;
  return pdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Evaluate (const BsdfRecord& record) const noexcept -> Spectrum
{
  //! Lambert BRDF : $ \rho / \pi $
  return reflectance_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Sample (BsdfRecord *record, const Point2f &sample)
  const noexcept -> Spectrum
{
  // Sample the incident direction in BRDF coordinates.
  const Vector3f incident = SampleCosineHemisphere (sample);
  record->SetIncident (incident);

  // Compute the PDF.
  const Float pdf = Pdf (*record);
  record->SetPdf (pdf);

  // Compute the BRDF.
  const Spectrum brdf = Evaluate (*record);
  record->SetBsdf (brdf);

  return brdf;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

