/*!
 * @file rectangle.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "bounds2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
Bounds2<T>::Bounds2 (T first_x, T first_y, T last_x, T last_y) :
  min_ (std::make_pair (first_x, first_y)),
  max_ (std::make_pair (last_x,   last_y))
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Bounds2<T>::Min () const -> Vector2f
{
  return min_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Bounds2<T>::Max () const -> Vector2f
{
  return max_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Bounds2<T>::SetMin (T x, T y) -> void
{
  if (x < min_.X ())
  {
    min_.SetX (x);
  }
  if (y < min_.Y ())
  {
    min_.SetY (y);
  }
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto Bounds2<T>::SetMax (T x, T y) -> void
{
  if (max_.X () < x)
  {
    max_.SetX (x);
  }
  if (max_.Y () < y)
  {
    max_.SetY (y);
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
