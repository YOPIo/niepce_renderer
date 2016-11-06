#include "light.h"

namespace niepce
{

Light::Light()
{}

Light::Light(const char* name,
             const Rgb&  emission,
             const Rgb&  reflectance) :
    Material(name, emission, reflectance)
{}

Light::~Light()
{}

auto Light::Eval(const glm::vec3 &in,
                 const glm::vec3 &normal,
                 const glm::vec3 &out) const -> Rgb
{
  ERROR("Unexpected valuation at light material.");
  return glm::vec3();
}

auto Light::Sample(Random& random,
                   const glm::vec3& in,
                   const glm::vec3& normal,
                   Float*   pdf,
                   Rgb*             brdf) const -> Rgb
{
  ERROR("Unexpected valuation at light material.");
  return glm::vec3();
}

} // namespace niecpe
