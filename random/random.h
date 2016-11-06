#ifndef _RANDOM_H_
#define _RANDOM_H_

#include <limits>

namespace niepce
{
class Xorshift
{
 public:
  Xorshift() = delete;
  Xorshift(const unsigned long long seed);
  virtual ~Xorshift() = default;

  Xorshift(const Xorshift& Name) = delete;
  Xorshift(Xorshift&& Name) = delete;
  Xorshift& operator = (const Xorshift& Name) = delete;
  Xorshift& operator = (Xorshift&& Name) = delete;

  auto Next01() -> double;
  auto Next(double min, double max) -> double;
  auto Next() -> unsigned long long;

 private:
  unsigned long long x;
};

using Random = Xorshift;

}

#endif // _RANDOM_H_
