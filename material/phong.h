#ifndef _PHONG_H_
#define _PHONG_H_

#include "../core/common.h"
#include "material.h"

namespace niepce
{

class Phong : public Material
{
 public:
  Phong();
  Phong(const char* name,
        const glm::vec3& emission,
        const glm::vec3& reflectance,
        Float n);
  virtual ~Phong();

  Phong(const Phong& phong) = default;
  Phong(Phong&& phong)      = default;
  Phong& operator = (const Phong& phong) = default;
  Phong& operator = (Phong&& phong)      = default;

  auto Eval(const glm::vec3& in,
            const glm::vec3& normal,
            const glm::vec3& out) const -> Rgb;

  auto Sample(Random&          random,
              const glm::vec3& in,
              const glm::vec3& normal,
              Float*           pdf,
              Rgb*             brdf) const -> Rgb;
 private:
  Float n_;
};


}

#endif // _PHONG_H_
