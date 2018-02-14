#include "film.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Film::Film (const std::string& filename, uint32_t width, uint32_t height) :
    fullpath_ (filename),
    width_    (width),
    height_   (height),
    diagonal_ (std::sqrt (width * width + height * height)),
    pixels_   (new Film::Pixel [width * height])
{}
/*
// ---------------------------------------------------------------------------
*/
auto Film::operator () (Index x, Index y) const -> Film::Pixel
{
  return pixels_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::operator () (Index x, Index y) -> Film::Pixel&
{
  return pixels_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::At (Index x, Index y) const -> Film::Pixel
{
  return pixels_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
auto Film::At (Index x, Index y) -> Film::Pixel&
{
  return pixels_[y * width_ + x];
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/

