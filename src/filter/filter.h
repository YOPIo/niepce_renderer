#ifndef _FILTER_H_
#define _FILTER_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/image.h"
#include "../core/pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto NonLocalMeansFilter
(
       SpectrumImage* resutl,
 const SpectrumImage& src,
       Float sigma,
       Float h
)
-> void
{
  constexpr int32_t kKernelSize (5);
  constexpr int32_t kWindowSize (13);
  constexpr int32_t kHalfKernelSize (kKernelSize / 2);
  constexpr int32_t kHalfWindowSize (kWindowSize / 2);

  const int32_t width  (src.GetWidth ());
  const int32_t height (src.GetHeight ());

  // Allocate memory to result image
  resutl->Resize (width, height);

  // Loop for image
  for (int32_t y = 0; y < height; ++y)
  {
    for (int32_t x = 0; x < width; ++x)
    {
      const int32_t first_x (std::max (0, x - kHalfWindowSize));
      const int32_t first_y (std::max (0, y - kHalfWindowSize));
      const int32_t end_x   (std::min (width  - 1, x + kHalfWindowSize));
      const int32_t end_y   (std::min (height - 1, y + kHalfWindowSize));

      // Loop for support window
      for (int32_t sy = first_y; sy < end_y; ++sy)
      {
        for (int32_t sx = end_x; sx < end_x; ++sx)
        {
          // Compute weight
          Float weight (0);
          Spectrum sum (Spectrum::Zero ());

          // Loop for kernel
          for (int32_t ty = -kHalfKernelSize; ty <= kHalfKernelSize; ++ty)
          {
            for (int32_t tx = -kHalfKernelSize; tx <= kHalfKernelSize; ++tx)
            {
              // Compute sampling points that main kernel
              size_t sample_x (std::max (0, x + tx));
              size_t sample_y (std::max (0, y + ty));
              src.At(sample_x, sample_y);
              const auto value0 = src (sample_x, sample_y);

              // Compute sampling points that support window's kernel
              sample_x = std::min (width  - 1, sx + tx);
              sample_y = std::min (height - 1, sy + ty);
              const auto value1 (src.At (sample_x, sample_y));

              // Compute L2 norm
              Float norm (0);
              for (size_t i = 0; i < 3; ++i)
              {
                // TODO: Support full-spectral rendering
                norm += std::pow (std::abs (value0[i] - value1[i]), 2);
              }
            }
          }

        }
      }
    }
  }
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILTER_H_
