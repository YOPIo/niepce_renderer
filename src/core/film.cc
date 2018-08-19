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
// #define STB_IMAGE_WRITE_IMPLEMENTATION
#include "../ext/stb/stb_image_write.h"
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
  bounds_   (width, height),
  diagonal_ (diagonal),
  data_     (new Spectrum [width * height])
{}
/*
// ---------------------------------------------------------------------------
*/
Film::Film (const Film &film) :
  diagonal_ (film.diagonal_),
  bounds_   (film.bounds_)
{
  const auto width  = static_cast <int> (film.Width ());
  const auto height = static_cast <int> (film.Height ());
  this->data_.reset (new Spectrum [width * height]);

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto index = y * width + x;
      this->data_[index] = film.data_[index];
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
Film::Film (Film &&film) :
  diagonal_ (film.Diagonal ()),
  bounds_   (film.bounds_)
{
  const auto width  = static_cast <int> (film.Width ());
  const auto height = static_cast <int> (film.Height ());
  this->data_.reset (new Spectrum [width * height]);

  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto index = y * width + x;
      this->data_[index] = film.data_[index];
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::SaveAs (const char *filename) const noexcept -> void
{
  const auto gammna = [] (Float val) -> Float
  {
    return std::pow (val, 1.0 / 2.2);
  };

  const auto width  = Width ();
  const auto height = Height ();
  auto img = new unsigned char [width * height * 4];
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      const auto index = y * width + x;
      img[4 * index + 0] = FloatToInt (gammna (data_[index].X ()));
      img[4 * index + 1] = FloatToInt (gammna (data_[index].Y ()));
      img[4 * index + 2] = FloatToInt (gammna (data_[index].Z ()));
      img[4 * index + 3] = 255;
    }
  }
  stbi_write_png (filename, width, height, 4, img, sizeof (unsigned char) * width * 4);
  delete [] img;
}
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
  const Float aspect = static_cast <Float> (bounds_.Height ())
                     / static_cast <Float> (bounds_.Width ());
  const Float x = std::sqrt (diagonal_ * diagonal_ / (1 + aspect * aspect));
  const Float y = aspect * x;
  return Bounds2f (Point2f (-x / 2.0, -y / 2.0), Point2f (x / 2.0, y / 2.0));
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::Resolution () const noexcept -> Bounds2f
{
  return Bounds2f (Point2f (0, 0), Point2f (bounds_.Width (), bounds_.Height ()));
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::ReplaceFilmTile (const FilmTile& tile) noexcept -> void
{
  const auto width = static_cast <int> (bounds_.Width ());
  for (int y = tile.Min().Y (); y < static_cast <int> (tile.Max ().Y ()); ++y)
  {
    for (int x = tile.Min().X (); x < static_cast <int> (tile.Max ().X ()); ++x)
    {
      const auto data = tile.At (x - tile.Min ().X (), y - tile.Min ().Y ());
      data_.get () [y * width + x] = data;
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::UpdateFilmTile (const FilmTile &tile) noexcept -> void
{
  std::exit (EXIT_FAILURE);
}
/*
// ---------------------------------------------------------------------------
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
*/
/*
// ---------------------------------------------------------------------------
*/
auto ToneMapping (Film *film) -> void
{
  Spectrum *luminances = new Spectrum [film->Width () * film->Height ()];
  const auto width  = film->Width ();
  const auto height = film->Height ();

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
      const auto index = y * width + x;
      const auto r = tone_mapping (film->data_[index].X ());
      const auto g = tone_mapping (film->data_[index].Y ());
      const auto b = tone_mapping (film->data_[index].Z ());
      film->data_[index] = Spectrum (r, g, b);
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
