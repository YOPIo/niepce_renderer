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
auto Film::ApplyDenoising () -> void
{
  const auto src = *this;
  const auto kernel_size = 5;
  const auto search_size = 13;
  const auto half_kernel_size = kernel_size / 2;
  const auto half_search_size = search_size / 2;
  const auto &width  = Width ();
  const auto &height = Height ();

  const auto h     = 0.5;
  const auto sigma = 0.5;

  // Get a kernel window.
  auto GetKernel = [&]
  (
   int x,
   int y,
   Image <Spectrum>* kernel
  ) -> void
  {
    // For each kernel pixel.
    for (int sy = 0; sy < kernel_size; ++sy)
    {
      for (int sx = 0; sx < kernel_size; ++sx)
      {
        int tx = std::max (0, x - half_kernel_size + sx);
        tx = std::min ((int)width - 1, x + half_kernel_size + sx);
        int ty = std::max (0, y - half_kernel_size + sy);
        ty = std::min ((int)height - 1, y + half_kernel_size + sy);
        kernel->SetValueAt (sx, sy, src.At (tx, ty));
      }
    }
  };

  auto L2Norm = [&]
  (
   const Image <Spectrum> &lhs,
   const Image <Spectrum> &rhs
  ) -> Float
  {
    Float sum = 0;
    for (int y = 0; y < kernel_size; ++y)
    {
      for (int x = 0; x < kernel_size; ++x)
      {
        const auto tmp = lhs.At (x, y) - rhs.At (x, y);
        sum += tmp.Length ();
      }
    }
    return sum;
  };

  // For each pixel.
  for (int y = 0; y < Height (); ++y)
  {
    for (int x = 0; x < Width (); ++x)
    {
      // Get kernel image.
      const auto target = Point2f (x, y);
      Image target_kernel (kernel_size, kernel_size);
      GetKernel (x, y, &target_kernel);

      Float    sum_weight = 0;
      Spectrum sum_pixel  = Spectrum::Zero ();

      // For each search window.
      for (int sy = y - half_search_size; sy <= y + half_search_size; ++sy)
      {
        for (int sx = x - half_search_size; sx <= x + half_search_size; ++sx)
        {
          auto tx = std::max (0, sx);
          tx = std::min (sx, (int)width - 1);

          auto ty = std::max (0, sy);
          ty = std::min (sy, (int)height - 1);

          // Get kernel.
          Image search_kernel (kernel_size, kernel_size);
          GetKernel (sx, sy, &search_kernel);

          const auto norm   = L2Norm (target_kernel, search_kernel);
          const auto tmp    = std::fmax (norm * norm - 2.0 * sigma * sigma, 0.0);
          const auto weight = std::exp (tmp / h * h);

          sum_weight += weight;
          sum_pixel  =  sum_pixel + src.At (tx, ty) * weight;
        }
      }
      this->SetValueAt (x, y, sum_pixel / sum_weight);
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
