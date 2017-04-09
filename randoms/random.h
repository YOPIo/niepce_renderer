#ifndef _RANDOM_H_
#define _RANDOM_H_

/* Our file includes */
#include "../core/niepce.h"

namespace niepce
{

class Random
{
 public:
  Random();
  virtual ~Random();

  Random(const Random& rnd) = default;
  Random(Random&& rnd)      = default;

  auto operator = (const Random& rnd) -> Random& = default;
  auto operator = (Random&& rnd)      -> Random& = default;

  /* Public methods */
  virtual auto Next01()     -> Float = 0;
  virtual auto NextUInt32() -> uint32_t = 0;
};


}  // namespace niepce

#endif // _RANDOM_H_
