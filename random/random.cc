#include "random.h"

namespace niepce
{

Xorshift::Xorshift(const unsigned long long seed)
{
  if (seed != 0)
  {
    x = seed;
  }else
  {
    x = 0xDEADBEEFDEADBEEF;
  }
}

auto Xorshift::Next01() -> double
{
  return static_cast<double>( Next() ) / std::numeric_limits<unsigned long long>::max();
}

auto Xorshift::Next(double min, double max) -> double
{
  const double inv = (max - min);
  return (static_cast<double>( Next() ) * (inv / std::numeric_limits<unsigned long long>::max())) + min;
}

auto Xorshift::Next() -> unsigned long long
{
  x ^= x >> 12;
  x ^= x << 25;
  x ^= x >> 27;
  return x * 2685821657736338717LL;
}



} // namespace niepce
