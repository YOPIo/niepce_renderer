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
  const auto& tmp = -intersection.Outgoing ();

  // Compute UV position of sphere.
  const auto theta = std::acos (tmp.Y ());
  auto phi = std::atan2 (tmp.X (), tmp.Z ());
  if (phi < 0.0) { phi += 2.0 * kPi; }
  const auto u = 1.0 - (phi / (2.0 * kPi));
  const auto v = (theta / kPi);
  const auto x = static_cast <int> ((image_->Width  () - 1) * u);
  const auto y = static_cast <int> ((image_->Height () - 1) * v);

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

