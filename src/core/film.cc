/*!
 * @file film.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "film.h"
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
Film::Film
(
 const char*  filename,
 unsigned int width,
 unsigned int height,
 Float        diagonal // (mm)
) :
  filename_   (filename),
  resolution_ (std::make_pair (width, height)),
  diagonal_   (diagonal * 0.001), // Convert mm to m.
  image_      (width, height)
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
auto Film::SetFilmTile (const FilmTile& tile) noexcept -> void
{
  const Bounds2f tile_bounds = tile.Bounds ();
  const unsigned int begin_x = tile_bounds.Min ().X ();
  const unsigned int begin_y = tile_bounds.Min ().Y ();
  const unsigned int last_x  = tile_bounds.Max ().X ();
  const unsigned int last_y  = tile_bounds.Max ().Y ();

  // Copy
  for (int y = begin_y; y <= last_y; ++y)
  {
    for (int x = begin_x; x <= last_x; ++x)
    {
      image_.Set (x, y, tile (x, y));
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

