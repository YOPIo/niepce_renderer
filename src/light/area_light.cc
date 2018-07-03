/*!
 * @file area.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "area_light.h"
#include "../core/attributes.h"
#include "../shape/shape.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
AreaLight::AreaLight
(
 const std::shared_ptr <Shape>& shape,
 const Spectrum& emission
) :
  Light (),
  shape_    (shape),
  emission_ (emission)
{}
/*
// ---------------------------------------------------------------------------
*/
AreaLight::AreaLight (const Spectrum& emission) :
  Light (),
  emission_ (emission),
  shape_ (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
auto AreaLight::Emission () const noexcept -> Spectrum
{
  return emission_;
}
/*
// ---------------------------------------------------------------------------
*/
auto AreaLight::Evaluate (Float* pdf) -> Spectrum
{
  *pdf = 1.0 / shape_->SurfaceArea ();
  return emission_;
}
/*
// ---------------------------------------------------------------------------
*/
auto AreaLight::Sample
(
 const Intersection& intersection,
 const Point2f& sample
)
  const noexcept -> Point3f
{
  return shape_->Sample (sample);
}
/*
// ---------------------------------------------------------------------------
*/
auto AreaLight::SamplePosition (const Point2f &sample)
  const noexcept -> Point3f
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateAreaLight (const Attributes& attrib) -> std::shared_ptr <AreaLight>
{
  const auto emission = attrib.FindSpectrum ("emission");
  return std::make_shared <AreaLight> (emission);
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateAreaLight
(
 const Attributes& attrib,
 const std::shared_ptr <Shape>& shape
)
  -> std::shared_ptr <AreaLight>
{
  const auto emission = attrib.FindSpectrum ("emission");
  return std::make_shared <AreaLight> (shape, emission);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
