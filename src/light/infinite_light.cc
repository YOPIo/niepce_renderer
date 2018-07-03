/*!
 * @file infinite_light.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "infinite_light.h"
#include "../core/transform.h"
#include "../core/attributes.h"
#include "../core/intersection.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
InfiniteLight::InfiniteLight
(
 const Transform& light_to_world,
 const char* filename
) :
  image_ (std::make_shared <ImageIO <Spectrum>> (filename))
{
  // Todo : use transform matrix.
}
/*
// ---------------------------------------------------------------------------
*/
auto InfiniteLight::Emission () const noexcept -> Spectrum
{
  return Spectrum::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto InfiniteLight::SamplePosition (const Point2f &sample) const noexcept
  -> Point3f
{
  std::cerr << "InfiniteLight::SamplePosition was called." << std::endl;
  return Point3f::Zero ();
}
/*
// ---------------------------------------------------------------------------
*/
auto InfiniteLight::Evaluate (const Intersection &intersection, Float* pdf)
  const noexcept -> Spectrum
{
  // Get a ray
  const auto& dir = -intersection.Outgoing ();

  // Compute UV position of sphere.
  const Float u = std::atan2 (dir.Z (), dir.X ()) / (2.0 * kPi) + 0.5;
  const Float v = std::asin (dir.Y ()) * 0.5 + 0.5;

  const unsigned int x = (u * (Float)image_->Width ());
  const unsigned int y = (v * (Float)image_->Height ());

  // ... ??
  *pdf = 1;

  const auto res = image_->At (x, y);
  return res;
}
/*
// ---------------------------------------------------------------------------
*/
auto InfiniteLight::Pdf () const noexcept -> Float
{
  std::cerr << "Error::InfiniteLight::Pdf was called." << std::endl;
  return 1;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateInfiniteLight (const Attributes& attributes)
  -> std::shared_ptr <InfiniteLight>
{
  // Get filename.
  const auto& filename = attributes.FindString ("filename");
  // Todo: support rotation.
  return std::make_shared <InfiniteLight> (Transform (), filename.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

