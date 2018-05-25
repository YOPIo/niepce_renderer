/*!
 * @file film.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "film.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Film::Film
(
 const char*  filename,
 unsigned int width,
 unsigned int height,
 Float        diagonal
) :
  filename_   (filename),
  resolution_ (std::make_pair (width, height)),
  diagonal_   (diagonal * 0.001)
{}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Diagonal () const noexcept -> Float
{
  return diagonal_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Height () const noexcept -> unsigned int
{
  return resolution_.second;
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Width () const noexcept -> unsigned int
{
  return resolution_.first;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

