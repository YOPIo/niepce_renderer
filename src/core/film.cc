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
 Float        diagonal
) :
  ImageIO <Spectrum> (filename, width, height),
  bounds_   (width, height),
  diagonal_ (diagonal)
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
auto Film::PhysicalBounds () const noexcept -> Bounds2f
{
  const Float aspect = static_cast <Float> (height_)
                     / static_cast <Float> (width_);
  const Float x = std::sqrt (diagonal_ * diagonal_ / (1 + aspect * aspect));
  const Float y = aspect * x;
  return Bounds2f (Point2f (-x / 2.0, -y / 2.0), Point2f (x / 2.0, y / 2.0));
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Resolution () const noexcept -> Bounds2f
{
  return Bounds2f (Point2f (0, 0), Point2f (width_, height_));
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::AddFilmTile (const FilmTile& tile) noexcept -> void
{
  const Point2f min = tile.Bounds ().Min ();
  const Point2f max = tile.Bounds ().Max ();
  // Range check
  if (bounds_.IsInside (min) && bounds_.IsInside (max))
  {
    auto copy = [&] (int x, int y) -> void
    {
      SetValueAt (x + min.X (), y + min.Y (), tile (x, y));
    };
    For2 (copy, tile.Width (), tile.Height ());
    return ;
  }
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

