#ifndef _TIMER_H_
#define _TIMER_H_

#include "niepce.h"

#include <chrono>
#include <thread>

namespace niepce
{

template <typename T = std::chrono::milliseconds>
class Time
{
 public:
  /* Time constructors */
  Time ();
  virtual ~Time ();

  Time (const Time&  time) = default;
  Time (      Time&& time) = default;

  /* Time operators*/
  auto operator = (const Time&  time) -> Time& = default;
  auto operator = (      Time&& time) -> Time& = default;

}; // class Time


}  // namespace niepce

#endif // _TIMER_H_
