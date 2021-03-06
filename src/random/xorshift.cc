/*!
 * @file xorshift.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "xorshift.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
XorShift::XorShift () :
  x_ (123456789),
  y_ (362436069),
  z_ (521288629),
  w_ (88675123 )
{}
/*
// ---------------------------------------------------------------------------
*/
XorShift::XorShift (std::uint_fast32_t seed)
{
  SetSeed (seed);
}
/*
// ---------------------------------------------------------------------------
*/
auto XorShift::SetSeed (int seed) noexcept -> void
{
  x_ = seed << 13;
  y_ = (seed >> 9) ^ (x_ << 6);
  z_ = y_ >> 7;
  w_ = seed;
}
/*
// ---------------------------------------------------------------------------
*/
auto XorShift::Next01 () noexcept -> Float
{
  const Float res =
    static_cast <float> (Next ()) / std::numeric_limits<uint_fast32_t>::max ();
  return Clamp (res);
}
/*
// ---------------------------------------------------------------------------
*/
auto XorShift::Next () noexcept -> std::uint_fast32_t
{
  std::uint_fast32_t t = (x_ ^ (x_ << 11));
  x_ = y_;
  y_ = z_;
  z_ = w_;
  return w_ = (w_ ^ (w_ >> 19)) ^ (t ^ (t >> 8));
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
