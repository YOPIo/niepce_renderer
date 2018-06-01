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
  tile_bounds_ (bound)
{}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::operator () (unsigned int x, unsigned int y)
  const noexcept -> Spectrum
{
  return data_[y * Width () + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::At (unsigned int x, unsigned int y) const -> Spectrum
{
  return data_.at (y * Width () + x);
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::Width () const noexcept -> unsigned int
{
  return tile_bounds_.Max (). X () - tile_bounds_.Min ().X ();
}
/*
// ---------------------------------------------------------------------------
*/
auto FilmTile::Height () const noexcept -> unsigned int
{
  return tile_bounds_.Max (). Y () - tile_bounds_.Min ().Y ();
}
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
auto FilmTile::SetSpectrumAt
(
 unsigned int x,
 unsigned int y,
 const Spectrum& s
)
  -> void
{
  const unsigned int width = Width ();
  data_[y * width + x] = s;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
