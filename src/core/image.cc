/*!
 * @file image.h
 * @brief The fundamental class for image.
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
Image::Image () :
  width_  (0),
  height_ (0),
  pixels_ (nullptr)
{}
/*
// ---------------------------------------------------------------------------
*/
Image::Image (unsigned int width, unsigned int height) :
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
auto Image::operator () (unsigned int x, unsigned int y) const -> Pixel
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
inline auto Image::Height () const noexcept -> unsigned int
{
  return height_;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Image::SetPixel
(
 unsigned int x,
 unsigned int y,
 const Pixel& p
)
  -> void
{
  if (width_ <= x || height_ <= y)
  {
    throw std::out_of_range ("");
  }
  pixels_[x * width_ + y] = p;
}
/*
// ---------------------------------------------------------------------------
*/
inline auto Image::Width () const noexcept -> unsigned int
{
  return width_;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
