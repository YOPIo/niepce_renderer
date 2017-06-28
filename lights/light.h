#ifndef _LIGHT_H_
#define _LIGHT_H_

#include "../core/niepce.h"
#include "../core/transform.h"

namespace niepce
{

enum class LightType : int
{
  kArea     = 0,
  kInfinite = 1
};

class Light
{
  /* Light constructors */
 public:
  Light () = delete;
  Light (LightType        type,
         unsigned int     num_samples,
         const Transform& local_to_world);
  virtual ~Light ();

  Light (const Light&  light) = default;
  Light (      Light&& light) = default;


  /* Light operators*/
 public:
  auto operator = (const Light& light) -> Light& = default;
  auto operator = (Light&& light)      -> Light& = default;


  /* Light protected data */
 protected:
  const LightType    type_;
  const unsigned int num_samples_;
  const Transform    local_to_world_;
  const Transform    world_to_local_;
}; // class Light


}  // namespace niepce

#endif // _LIGHT_H_
