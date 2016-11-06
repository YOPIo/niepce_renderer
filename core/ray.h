#ifndef _RAY_H_
#define _RAY_H_

#include "../3rdparty/glm/glm.hpp"

namespace niepce
{

struct Ray
{
 public:
  Ray() = default;
  Ray(const glm::vec3& org, const glm::vec3& dir);
  virtual ~Ray() = default;

  Ray(const Ray& ray) = default;
  Ray(Ray&& ray)      = default;
  Ray& operator = (const Ray& ray) = default;
  Ray& operator = (Ray&& ray)      = default;

  glm::vec3 origin_;
  glm::vec3 direction_;
}; // struct Ray

} // namespace niepce

#endif // _RAY_H_
