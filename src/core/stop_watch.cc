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
// Definition of ElapsedTime
// ---------------------------------------------------------------------------
*/
ElapsedTime::ElapsedTime
(
 unsigned int hours,
 unsigned int minutes,
 unsigned int seconds,
 unsigned int milliseconds
) :
  hours_        (hours),
  minutes_      (minutes),
  seconds_      (seconds),
  milliseconds_ (milliseconds)
{}
/*
// ---------------------------------------------------------------------------
*/
auto ElapsedTime::ToString () -> std::string
{
  
}
/*
// ---------------------------------------------------------------------------
// Definition of StopWatch
// ---------------------------------------------------------------------------
*/
auto StopWatch::Lap () const
  -> ElapsedTime
{

}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Reset () -> void
{

}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Split () const
  -> ElapsedTime
{

}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Start () -> void
{
  start_ = std::chrono::system_clock::now ();
}
/*
// ---------------------------------------------------------------------------
*/
auto StopWatch::Stop () const
  -> ElapsedTime
{
  auto diff = std::chrono::system_clock::now () - start_;

  unsigned int hours
    = std::chrono::duration_cast <std::chrono::hours> (diff).count ();
  unsigned int minutes
    = std::chrono::duration_cast <std::chrono::minutes> (diff).count ();
  unsigned int seconds
    = std::chrono::duration_cast <std::chrono::seconds> (diff).count ();
  unsigned int milliseconds
    = std::chrono::duration_cast <std::chrono::milliseconds> (diff).count ();

  std::cout << "hours        : " << hours
            << "minutes      : " << minutes
            << "second       : " << seconds
            << "milliseconds : " << milliseconds
            << std::endl;
  return ElapsedTime (1, 1, 1, 1);
}
/*
// ---------------------------------------------------------------------------
*/
