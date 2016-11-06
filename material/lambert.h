#ifndef _LAMBERT_H_
#define _LAMBERT_H_

#include "../core/common.h"
#include "material.h"
#include "../random/random.h"

namespace niepce
{

class Lambert : public Material
{
 public:
  Lambert();
  Lambert(const char* name,
          const glm::vec3& emission,
          const glm::vec3& reflectance);
  virtual ~Lambert();

  Lambert(const Lambert& lambert) = default;
  Lambert(Lambert&& lambert)      = default;
  Lambert& operator = (const Lambert& lambert) = default;
  Lambert& operator = (Lambert&& lambert)      = default;

  auto Eval(const glm::vec3& in,
            const glm::vec3& normal,
            const glm::vec3& out) const -> Rgb;

  auto Sample(Random&          random,
              const glm::vec3& in,
              const glm::vec3& normal,
              Float*           pdf,
              Rgb*             brdf) const -> Rgb;
 private:
};

} // namespace niepce

#endif // _LAMBERT_H_
