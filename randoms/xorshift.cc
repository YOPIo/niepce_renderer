#include "xorshift.h"

namespace niepce
{

// Default values
uint32_t XorShift::x_ = 123456789;
uint32_t XorShift::y_ = 362436069;
uint32_t XorShift::z_ = 521288629;
uint32_t XorShift::w_ = 88675123;


XorShift::XorShift()
{}

// Initialize with seed
XorShift::XorShift(uint64_t seed)
{
  x_ = seed << 13;
  y_ = (seed >> 9) ^ (x_ << 6);
  z_ = y_ >> 7;
  w_ = seed;
}

XorShift::~XorShift()
{}

auto XorShift::Next01() -> Float
{
  return static_cast<Float>( NextUInt32() ) / std::numeric_limits<uint32_t>::max();
}

auto XorShift::NextUInt32() -> uint32_t
{
  unsigned long t = (x_ ^ (x_ << 11));
  x_ = y_;
  y_ = z_;
  z_ = w_;
  return w_ = (w_ ^ (w_ >> 19)) ^ (t ^ (t >> 8));
}

}  // namespace niepce
