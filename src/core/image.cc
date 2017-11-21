#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Image3f
// ---------------------------------------------------------------------------
*/
Image3f::Image3f (size_t width, size_t height) :
  resolution_ (width, height),
  data_       (new Pixel [width * height])
{}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::operator () (size_t x, size_t y) -> Pixel&
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::operator () (size_t x, size_t y) const -> Pixel
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::At (size_t x, size_t y) -> Pixel&
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::At (size_t x, size_t y) const -> Pixel
{
  return data_ [y * resolution_.x + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::GetWidth () const -> uint32_t
{
  return resolution_.x;
}
/*
// ---------------------------------------------------------------------------
*/
auto Image3f::GetHeight () const -> uint32_t
{
  return resolution_.y;
}
/*
// ---------------------------------------------------------------------------
*/
auto CreateImage3f (size_t width, size_t height) -> ImagePtr
{
  return std::make_shared <Image3f> (width, height);
}
/*
// ---------------------------------------------------------------------------
*/
auto LoadImage (const char* filename) -> ImagePtr
{
  // Load width, height and image data as rgb (0 - 255)
  int width, height, n;
  unsigned char* data = stbi_load (filename, &width, &height, &n, 3);

  // Allocate memory
  ImagePtr ret (CreateImage3f (width, height));

  // Copy data
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      const Float r (data[y * width * 3 + x + 0]);
      const Float g (data[y * width * 3 + x + 1]);
      const Float b (data[y * width * 3 + x + 2]);
      (*ret) (x, y) = Pixel (r, g, n);
    }
  }

  // Free original image
  stbi_image_free (data);

  return std::move (ret);
}
/*
// ---------------------------------------------------------------------------
*/
auto LoadHdrImage (const char* filename) -> ImagePtr
{

  stbi_hdr_to_ldr_gamma(2.2f);
  stbi_hdr_to_ldr_scale(1.0f);

  int width, height, n;
  float* data = stbi_loadf (filename, &width, &height, &n, 4);

  // Allocate memory
  ImagePtr ret (CreateImage3f (width, height));

  // Copy data
  for (size_t y = 0; y < height; ++y)
  {
    for (size_t x = 0; x < width; ++x)
    {
      const Float r (data[y * width * 3 + x + 0]);
      const Float g (data[y * width * 3 + x + 1]);
      const Float b (data[y * width * 3 + x + 2]);
      (*ret) (x, y) = Pixel (r, g, n);
    }
  }

  // Free original image
  stbi_image_free (data);

  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
