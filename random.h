#ifndef _RANDOM_H_
#define _RANDOM_H_

#include "niepce.h"

class XorShift
{
 public:
  XorShift()
  {};
  virtual ~XorShift()
  {};

  XorShift(const XorShift& rng) = delete;
  XorShift(XorShift&& rng)      = delete;

  auto operator = (const XorShift& rng) -> XorShift& = delete;
  auto operator = (XorShift&& rng)      -> XorShift& = delete;

  // ---------------------------------------------------------------------------
  // XorShift public methods (static)
  // ---------------------------------------------------------------------------
  static auto Next01() -> float
  {
    const uint32_t rnd = NextUInt32();
    return static_cast<float>(rnd) /
        static_cast<float>(std::numeric_limits<uint32_t>::max());
  }

  static auto SetSeed(uint32_t seed) -> void
  {
    x_ = seed << 13;
    y_ = (seed >> 9) ^ (x_ << 6);
    z_ = y_ >> 7;
    w_ = seed;
  }


  // ---------------------------------------------------------------------------
  // XorShift private methods
  // ---------------------------------------------------------------------------
 private:
  static auto NextUInt32() -> uint32_t
  {
    unsigned long t = (x_ ^ (x_ << 11));
    x_ = y_;
    y_ = z_;
    z_ = w_;
    return w_ = (w_ ^ (w_ >> 19)) ^ (t ^ (t >> 8));
  }


  // ---------------------------------------------------------------------------
  // XorShift private member data
  // ---------------------------------------------------------------------------
 private:
  static uint32_t x_;
  static uint32_t y_;
  static uint32_t z_;
  static uint32_t w_;
};

// ---------------------------------------------------------------------------
// Initialization with default seeds
// ---------------------------------------------------------------------------
uint32_t XorShift::x_ = 123456789;
uint32_t XorShift::y_ = 362436069;
uint32_t XorShift::z_ = 521288629;
uint32_t XorShift::w_ = 88675123;

#endif // _RANDOM_H_
