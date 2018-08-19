/*!
 * @file stop_watch.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/27
 * @details 
 */
#include "stop_watch.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Definition of ElapsedTime
// ---------------------------------------------------------------------------
*/
ElapsedTime::ElapsedTime (uint64_t t)
{
  uint64_t tmp = static_cast <uint64_t> (std::floor (t * 0.001));
  minutes_ = tmp / 60;
  seconds_ = tmp % 60;
  milliseconds_ = t % 1000;
}
/*
// ---------------------------------------------------------------------------
*/
auto ElapsedTime::ToString () -> std::string
{
  return std::to_string (minutes_) + "m " + std::to_string(seconds_) + "s "
       + std::to_string (milliseconds_) + "ms";
}
/*
// ---------------------------------------------------------------------------
// Definition of StopWatch
// ---------------------------------------------------------------------------
*/
auto StopWatch::Lap ()
  -> ElapsedTime
{
  const auto now = std::chrono::system_clock::now ();
  const auto diff = now - lap_;
  const uint64_t t
    = std::chrono::duration_cast <std::chrono::milliseconds> (diff).count ();
  lap_ = now;
  return ElapsedTime (t);
}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Reset () -> void
{
  lap_ = start_ = std::chrono::system_clock::now ();
}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Split () const
  -> ElapsedTime
{
  auto diff = std::chrono::system_clock::now () - start_;
  uint64_t t
    = std::chrono::duration_cast <std::chrono::milliseconds> (diff).count ();
  return ElapsedTime (t);
}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Start () -> void
{
  start_ = std::chrono::system_clock::now ();
  lap_   = start_;
}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Stop () const
  -> ElapsedTime
{
  auto diff = std::chrono::system_clock::now () - start_;
  uint64_t t
    = std::chrono::duration_cast <std::chrono::milliseconds> (diff).count ();
  return ElapsedTime (t);
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
