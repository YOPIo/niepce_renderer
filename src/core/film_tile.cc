/*!
 * @file film_tile.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "film_tile.h"
#include "vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
FilmTile::FilmTile (const Bounds2f& bound) :
  ImageIO <Spectrum> (bound.Width (), bound.Height ()),
  tile_bounds_ (bound)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::Bounds () const noexcept -> Bounds2f
{
  return tile_bounds_;
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::Min () const noexcept -> Point2f
{
  return tile_bounds_.Min ();
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::Max () const noexcept -> Point2f
{
  return tile_bounds_.Max ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
