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
Lambert::Lambert
(
 const Intersection& intersection,
 const Spectrum& reflectance
) :
  Bsdf (intersection),
  reflectance_ (reflectance)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Pdf (const BsdfRecord& record)
  const noexcept -> Float
{
  const Vector3f incident = record.Incident ();

  //! Lambert PDF : $ cos\theta / \pi $
  const Float pdf = std::fabs (bsdf::CosTheta (incident) / kPi);
  return pdf;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Evaluate (const BsdfRecord& record) const noexcept -> Spectrum
{
  //! Lambert BRDF : $ \rho / \pi $
  return reflectance_ / kPi;
}
/*
// ---------------------------------------------------------------------------
*/
auto Lambert::Sample (BsdfRecord *record, const Point2f &sample)
  const noexcept -> Vector3f
{
  // Sample the incident direction in BRDF coordinates.
  const Vector3f incident = SampleCosineHemisphere (sample);
  record->SetIncident (Normalize (incident));

  // Compute the PDF.
  const Float pdf = Pdf (*record);
  record->SetPdf (pdf);

  // Compute the BRDF.
  const Spectrum brdf = Evaluate (*record);
  record->SetBsdf (brdf);

  // Compute the $ cos(\theta) $
  const Float cos_t = bsdf::Dot (incident);
  record->SetCosTheta (cos_t);

  return this->ToWorld (incident);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

