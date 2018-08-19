/*!
 * @file clipping_film.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#include "clipping_film.h"
#include "pixel.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
ClippingFilm::ClippingFilm (uint32_t first_x, uint32_t first_y,
                            uint32_t last_x,  uint32_t last_y) :
  area_ (first_x, first_y, last_x, last_y),
  film_ (last_x - first_x + 1, last_y - first_y + 1)
{}
/*
// ---------------------------------------------------------------------------
*/
auto ClippingFilm::operator () (uint32_t x, uint32_t y) const -> Pixel
{
  try
  {
    return film_ (x, y);
  }
  catch (const std::exception& e)
  {
    throw e;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto ClippingFilm::operator () (uint32_t x, uint32_t y) -> Pixel&
{
  try
  {
    return film_ (x, y);
  }
  catch (const std::exception& e)
  {
    throw e;
  }
}
/*
// ---------------------------------------------------------------------------
*/
auto ClippingFilm::Bounds2 () const -> Bounds2ui
{
  return area_;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
