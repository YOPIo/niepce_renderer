#ifndef _XORSHIFT_H_
#define _XORSHIFT_H_

#include "../core/niepce.h"

#include <climits>
#include <inttypes.h>

namespace niepce
{

class XorShift
{
 public:
  XorShift();
  XorShift(uint64_t seed);
  virtual ~XorShift();

  XorShift(const XorShift& rnd) = default;
  XorShift(XorShift&& rnd)      = default;


  // ---------------------------------------------------------------------------
  // XorShift public operators
  // ---------------------------------------------------------------------------
 public:
  auto operator = (const XorShift& rnd) -> XorShift& = default;
  auto operator = (XorShift&& rnd)      -> XorShift& = default;


  // ---------------------------------------------------------------------------
  // XorShift public methods
  // ---------------------------------------------------------------------------
 public:
  static auto Next01()     -> Float;
  static auto NextUInt32() -> uint32_t;

 private:
  static uint32_t x_;
  static uint32_t y_;
  static uint32_t z_;
  static uint32_t w_;
};

}  // namespace niepce

#endif // _XORSHIFT_H_
