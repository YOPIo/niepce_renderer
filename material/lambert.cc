#include "lambert.h"

namespace niepce
{

Lambert::Lambert()
{}

Lambert::Lambert(const char*      name,
                 const glm::vec3& emission,
                 const glm::vec3& reflectance) :
    Material(name, emission, reflectance)
{}

Lambert::~Lambert()
{}

auto Lambert::Eval(const glm::vec3& in,
                   const glm::vec3& normal,
                   const glm::vec3& out) const -> Rgb
{
  return reflectance_ / kPi;
}

auto Lambert::Sample(Random& random,
                     const glm::vec3& in,
                     const glm::vec3& normal,
                     Float* pdf,
                     Rgb*   brdf) const -> Rgb
{
  glm::vec3 binormal, tangent, now_normal = normal;
  if (abs(normal.x) > abs(normal.y))
  {
    tangent = glm::normalize(glm::cross(glm::vec3(0, 1, 0), normal));
  }
  else
  {
    tangent = glm::normalize(glm::cross(glm::vec3(1, 0, 0), normal));
  }
  binormal = glm::normalize(glm::cross(normal, tangent));

  const Float phi = random.Next(0.0, 2.0 * kPi);
  const Float r2  = random.Next01();
  const Float r2s = sqrt(r2);
  const Float tx  = r2s * cos(phi);
  const Float ty  = r2s * sin(phi);
  const Float tz  = sqrt(1.0 - r2);

  const glm::vec3 dir = tz * normal + tx * tangent + ty * binormal;

  if (pdf != NULL)
  {
    *pdf = glm::dot(normal, dir) / kPi;
  }
  if (brdf != NULL)
  {
    *brdf = Eval(in, normal, dir);
  }
  return dir;
}

} // namespace niepce
