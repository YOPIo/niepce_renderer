#include "phong.h"

namespace niepce
{

Phong::Phong()
{}

Phong::Phong(const char* name,
             const glm::vec3& emission,
             const glm::vec3& reflectance,
             Float n) :
    Material(name, emission, reflectance),
    n_(n)
{}

Phong::~Phong()
{}

auto Phong::Eval(const glm::vec3& in,
                 const glm::vec3& normal,
                 const glm::vec3& out) const -> Rgb
{
  if (glm::dot(normal, out) < 0.0)
  {
    return glm::vec3(0.0, 0.0, 0.0);
  }
  const glm::vec3 reflection_dir = glm::normalize(in - normal * 2.0f * dot(normal, in));
  double cosa = dot(reflection_dir, out);
  if (cosa < 0)
  {
    cosa = 0.0;
  }
  return reflectance_ * (n_ + 2.0f) / (2.0f * kPi) * static_cast<float>(std::pow(cosa, n_));
}

auto Phong::Sample(Random&          random,
                   const glm::vec3& in,
                   const glm::vec3& normal,
                   Float*           pdf,
                   Rgb*             brdf) const -> Rgb
{
  glm::vec3 dir;
  const glm::vec3 reflection_dir = reflect(in, normal);
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

  const Float u1 = random.Next01();
  const Float u2 = random.Next01();

  const Float phi = u1 * 2.0 * kPi;
  const Float theta = acos(pow(u2, 1 / (n_ + 1)));

  dir = tangent * (float)sin(theta) * (float)cos(phi) + reflection_dir * (float)cos(theta) + binormal * (float)sin(theta) * (float)sin(phi);

  if (pdf != NULL)
  {
    double cosa = dot(reflection_dir, dir);
    if (cosa < 0)
      cosa = 0.0;
    *pdf = (n_ + 1.0) / (2.0 * kPi) * pow(cosa, n_);
  }
  if (brdf != NULL) {
    *brdf = Eval(in, normal, dir);
  }

  return dir;
}

} // namespace niepce
