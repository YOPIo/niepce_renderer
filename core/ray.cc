#include "ray.h"

namespace niepce
{

Ray::Ray(const glm::vec3& org, const glm::vec3& dir) :
    origin_(org),
    direction_(dir)
{}

} // namespace niepce
