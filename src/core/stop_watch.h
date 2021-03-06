/*!
 * @file stop_watch.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/27
 * @details 
 */
#ifndef _STOP_WATCH_H_
#define _STOP_WATCH_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @struct ElapsedTime
//! @brief 
//! @details 
//! ----------------------------------------------------------------------------
class ElapsedTime
{
public:
  ElapsedTime () = delete;

  //! The constructor takes milliseconds
  ElapsedTime (uint64_t t);

  //! Copy constructor
  ElapsedTime(const ElapsedTime& elapsed) = default;

  //! Move constructor
  ElapsedTime(ElapsedTime&& elapsed) = default;

  //! Destructor
  virtual ~ElapsedTime () = default;

  //! Copy assignment operator
  auto operator = (const ElapsedTime& elapsed) -> ElapsedTime& = default;

  //! Move assignment operator
  auto operator = (ElapsedTime&& elapsed) -> ElapsedTime& = default;

public:
  /*!
   * @fn std::string ToString ()
   * @brief Return the string format X hours X minutes X seconds X milliseconds.
   * @return std::string
   * @exception none
   * @details
   */
  auto ToString () -> std::string;

  uint64_t minutes_;
  uint64_t seconds_;
  uint64_t milliseconds_;

  int sec;
};
//! ----------------------------------------------------------------------------
//! @class StopWatch
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class StopWatch final
{
public:
  //! The default class constructor.
  StopWatch () = default;

  //! The copy constructor of the class.
  StopWatch (const StopWatch& stopwatch) = default;

  //! The move constructor of the class.
  StopWatch (StopWatch&& stopwatch) = default;

  //! The default class destructor.
  virtual ~StopWatch () = default;

  //! The copy assignment operator of the class.
  auto operator = (const StopWatch& stopwatch) -> StopWatch& = default;

  //! The move assignment operator of the class.
  auto operator = (StopWatch&& stopwatch) -> StopWatch& = default;

public:
  //! @fn void Lap ()
  //! @brief Elapsed time from section.
  //! @return 
  //! @exception none
  //! @details 
  auto Lap () -> ElapsedTime;

  //! @fn void Reset ()
  //! @brief Reset a measuring time to 0 second.
  //! @return 
  //! @exception none
  //! @details 
  auto Reset () -> void;

  //! @fn void Split ()
  //! @brief Elapsed time from beginning.
  //! @return 
  //! @exception none
  //! @details 
  auto Split () const -> ElapsedTime;

  //! @fn void Start ()
  //! @brief Start a measuring time.
  //! @return none
  //! @exception none
  //! @details 
  auto Start () -> void;

  //! @fn void Stop ()
  //! @brief Stop a measuring time. You can restart measuring with Start () method.
  //! @return 
  //! @exception none
  //! @details 
  auto Stop () const -> ElapsedTime;

private:
  std::chrono::system_clock::time_point start_;
  std::chrono::system_clock::time_point lap_;
}; // class StopWatch
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _STOP_WATCH_H_
