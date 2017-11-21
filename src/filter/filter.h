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
template <typename T>
auto NonLocalMeansFilter
(
 const ImagePtr <T>& src,
       Float        sigma,
       Float         h
)
-> ImagePtr <T>
{
  const int kKernelSize (5);
  const int kWindowSize (13);

  const int width  (src->GetWidth ());
  const int height (src->GetHeight ());

  // Allocate memory to result image
  ImagePtr <T> result = CreateImage3 <T> (width, height);

  // Kernels to compute the weight
  ImagePtr <T> main_kernel    (CreateImage3 <T> (kKernelSize, kKernelSize));
  ImagePtr <T> support_kernel (CreateImage3 <T> (kKernelSize, kKernelSize));

  // Lambda that creating a kernel from image
  auto create_kernel_from = [&src, &kKernelSize] (int tx, int ty)
    -> ImagePtr <T>
  {
    ImagePtr <T> res (CreateImage3 <T> (kKernelSize, kKernelSize));
    for (int y = 0; y < kKernelSize; ++y)
    {
      for (int x = 0; x < kKernelSize; ++x)
      {
        const int idx_x (std::max (0, tx - kKernelSize / 2 + x));
        const int idx_y (std::max (0, ty - kKernelSize / 2 + y));
        (*res) (x, y) = (*src) (idx_x, idx_y);
      }
    }
    return res;
  };

  // Compute the weight of two kernels
  auto weight_from_kernels = [&kKernelSize]
  (
   const ImagePtr <T>& k0,
   const ImagePtr <T>& k1
  ) -> Float
  {
    Float weight (0);
    for (int y = 0; y < kKernelSize; ++y)
    {
      for (int x = 0; x < kKernelSize; ++x)
      {
        weight += std::pow ((*k0) (x, y).r_ - (*k1) (x, y).r_, 2);
        weight += std::pow ((*k0) (x, y).g_ - (*k1) (x, y).g_, 2);
        weight += std::pow ((*k0) (x, y).b_ - (*k1) (x, y).b_, 2);
      }
    }
    return weight;
  };

  // Loop for image
  for (int y = 0; y < height; ++y)
  {
    for (int x = 0; x < width; ++x)
    {
      // Create kernel based on current pixel (x, y)
      main_kernel = create_kernel_from (x, y);

      // Compute support window indices
      const int first_x (std::max (0, x - kWindowSize / 2));
      const int first_y (std::max (0, y - kWindowSize / 2));
      const int end_x   (std::min (width  - 1, x + kWindowSize / 2));
      const int end_y   (std::min (height - 1, y + kWindowSize / 2));

      // Loop for support window
      Float sum_weight (0);
      Pixel <T> sum_pixel;
      for (int sy = first_y; sy < end_y; ++sy)
      {
        for (int sx = end_x; sx < end_x; ++sx)
        {
          // Create kernel based on support window pixel (sx, sy)
          support_kernel = create_kernel_from (sx, sy);

          // Compute weight
          const Float weight (weight_from_kernels (main_kernel, support_kernel));
          const Float arg (std::fmax (weight - 2 * sigma * sigma, 0));
          const Float w (std::exp (arg));

          sum_weight += w;
          sum_pixel  += (*src) (sx, sy) * weight;
        }
      }

      (*result) (x, y) = sum_pixel / sum_weight;
    }
  }

  return result;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILTER_H_
