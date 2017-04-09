#ifndef _XORSHIFT_H_
#define _XORSHIFT_H_

/* Our file includes */
#include "../core/niepce.h"
#include "random.h"

/* std includes */
#include <climits>
#include <inttypes.h>

namespace niepce
{

class XorShift : public Random
{
 public:
  XorShift();
  XorShift(uint64_t seed);
  virtual ~XorShift();

  XorShift(const XorShift& rnd) = default;
  XorShift(XorShift&& rnd)      = default;

  auto operator = (const XorShift& rnd) -> XorShift& = default;
  auto operator = (XorShift&& rnd)      -> XorShift& = default;

  /* Public methods */
  auto Next01()     -> Float;
  auto NextUInt32() -> uint32_t;

 private:
  uint32_t x_;
  uint32_t y_;
  uint32_t z_;
  uint32_t w_;
};

}  // namespace niepce

#endif // _XORSHIFT_H_
