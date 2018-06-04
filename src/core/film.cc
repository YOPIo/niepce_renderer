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
  resolution_ (Bounds2f (Point2f (0, 0), Point2f(width, height))),
  diagonal_   (diagonal * 0.001) // Convert mm to m.
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
  const Float aspect = resolution_.Height () / resolution_.Width ();
  const Float x = std::sqrt (diagonal_ * diagonal_ / (1 + aspect * aspect));
  const Float y = aspect * x;
  return Bounds2f (Point2f (-x / 2.0, -y / 2.0), Point2f (x / 2.0, y / 2.0));
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::RenderingBounds () const noexcept -> Bounds2f
{
  // TODO: くけいれんだりんぐ
  return resolution_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Resolution () const noexcept -> Bounds2f
{
  return resolution_;
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Save () const noexcept -> void
{
  SaveAs (filename_.c_str ());
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::SaveAs (const char *filename) const noexcept -> void
{
  
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::AddFilmTile (const FilmTile& tile) noexcept -> void
{
  tiles_.push_back (tile);
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

