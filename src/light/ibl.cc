#include "ibl.h"

namespace niepce
{

Ibl::Ibl () :
  Light (LightType::kImageBased)
{}

Ibl::Ibl (const std::string& filepath) :
    Light (LightType::kImageBased)
{
  Load (filepath);
}

Ibl::~Ibl ()
{}

auto Ibl::Emission
(
 const Ray& ray
)
const -> Spectrum
{
  // Rotate the IBL
  const Float angle = kPi / 2;
  Matrix4x4<Float> m (std::cos (angle), -std::sin (angle), 0, 0,
                      std::sin (angle),  std::cos (angle), 0, 0,
                                     0,                 0, 0, 0,
                                     0,                 0, 0, 0);


  // Transform to light coordinates system
  const Vector3f direction = Normalize (ray.direction);

  // Float u = 0.5 + std::atan2 (direction.y, direction.x) / (2.0 * kPi);
  // Float v = 0.5 - std::asin (direction.y) / kPi;
  // u = Clamp (u, 0, 1);
  // v = Clamp (v, 0, 1);

  // Compute (u, v) from outgoing direction in spherical coordinate system
  const Float theta = SphericalTheta (direction);
  const Float phi   = SphericalPhi (direction);

  const Point2f st (phi / (2.0 * kPi), theta / kPi);

  // return image_ (Point2f (u, v));
  return image_ (st);
}

auto Ibl::Load (const std::string& filepath) -> void
{
  image_.Load (filepath);
}

}  // namespace niepce
