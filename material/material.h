#ifndef _MATERIAL_H_
#define _MATERIAL_H_

#include <memory>
#include <string>

#include "../3rdparty/glm/glm.hpp"
#include "../core/common.h"
#include "../random/random.h"

namespace niepce
{

class Material
{
 public:
  Material();
  Material(const char* name,
           const Rgb&  emission,
           const Rgb&  reflectance);
  virtual ~Material();

  Material(const Material& mtl) = default;
  Material(Material&& mtl)      = default;
  Material& operator = (const Material& mtl) = default;
  Material& operator = (Material&& mtl)      = default;

  auto Name() const -> std::string;
  auto Emission() const -> Rgb;
  auto Reflectance() const -> Rgb;

  virtual auto Eval(const glm::vec3& in,
                    const glm::vec3& normal,
                    const glm::vec3& out) const -> Rgb = 0;
  virtual auto Sample(Random& random,
                      const glm::vec3& in,
                      const glm::vec3& normal,
                      Float*   pdf,
                      Rgb*             brdf) const -> Rgb = 0;

 protected:
  std::string name_;
  Rgb emission_;
  Rgb reflectance_;
};

} // namespace niepce

#endif // _MATERIAL_H_
