/*!
 * @file image.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#include "image.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Image::Image (uint32_t width, uint32_t height) :
  width_  (width),
  height_ (height),
  pixels_ (new Pixel[width * height])
{
  for (int i = 0; i < width * height; ++i)
  {
    pixels_[i] = Pixel ();
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto Image::operator () (int32_t x, int32_t y) const -> Pixel
{
  if (width_ <= x || height_ <= y)
  {
    throw std::out_of_range ("");
  }
  return pixels_[x * width_ + y];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image::operator () (int32_t x, int32_t y) -> Pixel&
{
  if (width_ <= x || height_ <= y)
  {
    throw std::out_of_range ("");
  }
  return pixels_[x * width_ + y];
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
