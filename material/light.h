#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "material.h"
#include "../core/common.h"

namespace niepce
{

class Light : public Material
{
 public:
  Light();
  Light(const char* name,
        const Rgb&  emission,
        const Rgb&  reflectance);
  virtual ~Light();

  Light(const Light& light) = default;
  Light(Light&& light)      = default;
  Light& operator = (const Light& light) = default;
  Light& operator = (Light&& light)      = default;

  virtual auto Eval(const glm::vec3& in,
                    const glm::vec3& normal,
                    const glm::vec3& out) const -> Rgb;
  virtual auto Sample(Random& random,
                      const glm::vec3& in,
                      const glm::vec3& normal,
                      Float*   pdf,
                      Rgb*             brdf) const -> Rgb;
};


} // namespace niepce

#endif // _LIGHT_H_
