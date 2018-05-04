/*!
 * @file tile.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/29
 * @details 
 */
#include "tile.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Tile::Tile (const Bounds2f& bounds) :
  bounds_ (bounds),
  image_  (bounds_.Max ().X () - bounds_.Min ().X (), // Width of image.
           bounds_.Max ().Y () - bounds_.Min ().Y ()) // Height of image.
{}
/*
// ---------------------------------------------------------------------------
*/
auto Tile::Height () const -> unsigned int
{
  try
  {
    return image_.Height ();
  }
  catch (const std::exception& e)
  {
    throw e;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Tile::RenderingArea () const noexcept -> Bounds2f
{
  return bounds_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Tile::Width () const -> unsigned int
{
  try
  {
    return image_.Width ();
  }
  catch (const std::exception& e)
  {
    throw e;
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
