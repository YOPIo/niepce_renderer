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
auto Film::ReplaceFilmTile (const FilmTile& tile) noexcept -> void
{
  for (int y = tile.Min().Y (); y < static_cast <int> (tile.Max ().Y ()); ++y)
  {
    for (int x = tile.Min().X (); x < static_cast <int> (tile.Max ().X ()); ++x)
    {
      const auto data = tile.At (x - tile.Min ().X (), y - tile.Min ().Y ());
      SetValueAt (x, y, data);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::UpdateFilmTile (const FilmTile &tile) noexcept -> void
{
  for (int y = tile.Min().Y (); y < static_cast <int> (tile.Max ().Y ()); ++y)
  {
    for (int x = tile.Min().X (); x < static_cast <int> (tile.Max ().X ()); ++x)
    {
      const auto &val1 = this->At (x, y);
      const auto &val2 = tile.At (x - tile.Min ().X (), y - tile.Min ().Y ());
      SetValueAt (x, y, (val1 + val2));
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Denoising (Film *film) -> void
{
  const auto src = Film (*film);
  const auto kernel_size = 3;
  const auto search_size = 5;
  const auto half_kernel_size = kernel_size / 2;
  const auto half_search_size = search_size / 2;
  const auto &width  = src.Width ();
  const auto &height = src.Height ();

  const auto h     = 0.01;
  const auto sigma = 0.01;

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
        sum += tmp.X () * tmp.X ();
        sum += tmp.Y () * tmp.Y ();
        sum += tmp.Z () * tmp.Z ();
      }
    }
    return sum;
  };

  // For each pixel.
  for (int y = 0; y < src.Height (); ++y)
  {
    for (int x = 0; x < src.Width (); ++x)
    {
      // Get kernel image.
      const auto target = Point2f (x, y);
      Image <Spectrum> target_kernel (kernel_size, kernel_size);
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
          Image <Spectrum> search_kernel (kernel_size, kernel_size);
          GetKernel (tx, ty, &search_kernel);

          const auto norm   = L2Norm (target_kernel, search_kernel);
          const auto tmp    = std::fmax (norm * norm - 2.0 * sigma * sigma, 0.0);
          const auto weight = std::exp (-tmp / h * h);

          sum_weight += weight;
          sum_pixel  =  sum_pixel + src.At (tx, ty) * weight;
        }
      }
      film->SetValueAt (x, y, sum_pixel / sum_weight);
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto ToneMapping (Film *film) -> void
{
  Spectrum *luminances = new Spectrum [film->Width () * film->Height ()];
  const auto width  = film->Width ();
  const auto height = film->Height ();
  /*
  auto RgbToYCbCr = [] (const Spectrum &rgb) -> Spectrum
  {
    const auto r = rgb.X ();
    const auto g = rgb.Y ();
    const auto b = rgb.Z ();
    const auto y  = 0.183 * r + 0.614 * g + 0.062 * b + 16;
    const auto cb = -0.101 * r - 0.339 * g + 0.439 * b + 128;
    const auto cr = 0.439 * r - 0.399 * g - 0.040 * b + 128;
    return Spectrum (r, g, b);
  };
  auto YCbCrToRgb = [] (const Spectrum &ycbcr) -> Spectrum
  {
    const auto y  = ycbcr.X ();
    const auto cb = ycbcr.Y ();
    const auto cr = ycbcr.Z ();
    const auto r = 1.164 * (y - 16.0) + 1.793 * (cr - 128.0);
    const auto g = 1.164 * (y - 16.0) - 0.213 * (cb - 128.0) - 0.533 * (cr - 128.0);
    const auto b = 1.164 * (y - 16.0) + 2.112 * (cb - 128.0);
    return Spectrum (r, g, b);
  };

  // Conpute log average.
  Float sum = 0;
  Float max = 0;
  for (int y = 0; y < film->Height (); ++y)
  {
    for (int x = 0; x < film->Width (); ++x)
    {
      const auto l = RgbToYCbCr (film->At (x, y));
      luminances[y * width + x] = l;
      sum += std::log (kEpsilon + l.X ());
      max = std::fmax (max, l.X ());
    }
  }
  const auto lw = std::exp (sum / (film->Width () * film->Height ()));

  // Scaling
  for (int y = 0; y < film->Height (); ++y)
  {
    for (int x = 0; x < film->Width (); ++x)
    {
      const auto a = 0.18;
      luminances[y * width + x] = a / lw * luminances[y * width + x];
      // luminances[y * width + x].SetX (a / lw * luminances[y * width + x].X ());
    }
  }

  for (int y = 0; y < film->Height (); ++y)
  {
    for (int x = 0; x < film->Width (); ++x)
    {
      const auto l = luminances[y * width + x].X ();
      const auto tmp = (l * (1.0 + l / max * max)) / (1.0 + l);
      luminances[y * width + x].SetX (l);
      film->SetValueAt (x, y, YCbCrToRgb (luminances[y * width + x]));
    }
  }
  */

  /*
  for (int y = 0; y < film->Height (); ++y)
  {
    for (int x = 0; x < film->Width (); ++x)
    {
      const auto l     = RgbToLuminance (film->At (x, y));
      const auto scale = l != 0 ? (1.0f - std::exp(-l)) / l: 0.0f;
      const auto r     = std::fmin (scale * film->At (x, y).X (), 1.0);
      const auto g     = std::fmin (scale * film->At (x, y).Y (), 1.0);
      const auto b     = std::fmin (scale * film->At (x, y).Z (), 1.0);
      film->SetValueAt (x, y, Spectrum (r, g, b));
    }
  }
  */

  // Reinhard tone mapping
  /*
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto p   = film->At (x, y);
      const auto val = p / (Spectrum (1.0) + p);
    }
  }
  */

  // ACES Filmic Tonemapping Curve
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto tone_mapping = [] (Float val) -> Float
      {
        const auto a = 2.51;
        const auto b = 0.03;
        const auto c = 2.43;
        const auto d = 0.59;
        const auto e = 0.14;
        val = (val  * (a * val + b)) / (val * (c * val + d) + e);
        return Clamp (val, 0.0f, 1.0f);
      };
      const auto r = tone_mapping (film->At (x, y).X ());
      const auto g = tone_mapping (film->At (x, y).Y ());
      const auto b = tone_mapping (film->At (x, y).Z ());
      film->SetValueAt (x, y, Spectrum (r, g, b));
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
