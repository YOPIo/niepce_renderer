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
FilmTile::FilmTile (int tile_number, const Bounds2f& bound) :
  ImageIO <Spectrum> (bound.Width (), bound.Height ()),
  tile_number_ (tile_number),
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
auto FilmTile::TileNumber () const noexcept -> int
{
  return tile_number_;
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::ClearTileImage () noexcept -> void
{
  for (int y = 0; y < height_; ++y)
  {
    for (int x = 0; x < width_; ++x)
    {
      this->SetValueAt (x, y, Spectrum (0));
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
