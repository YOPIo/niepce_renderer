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
auto Film::ApplyToneMapping (Float key_value) -> void
{
  auto RgbToLuminance = [] (const Spectrum &rgb)
  {
    return 0.2126729 * rgb.X () + 0.7151522 * rgb.Y () + 0.0721750 * rgb.Z ();
  };

  for (int y = 0; y < Height (); ++y)
  {
    for (int x = 0; x < Width (); ++x)
    {
      const auto l     = RgbToLuminance (this->At (x, y));
      const auto scale = l != 0 ? (1.0f - std::exp(-l)) / l: 0.0f;
      const auto r     = std::fmin (scale * this->At (x, y).X (), 1.0);
      const auto g     = std::fmin (scale * this->At (x, y).Y (), 1.0);
      const auto b     = std::fmin (scale * this->At (x, y).Z (), 1.0);
      this->SetValueAt (x, y, Spectrum (r, g, b));
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
