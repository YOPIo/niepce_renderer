/*!
 * @file clipping_film.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _CLIPPING_FILM_H_
#define _CLIPPING_FILM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "image.h"
#include "bounds2.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class ClippingFilm
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ClippingFilm
{
public:
  //! The default class constructor.
  ClippingFilm () = delete;

  //! 
  ClippingFilm (uint32_t first_x, uint32_t first_y,
                uint32_t last_x,  uint32_t last_y);

  //! The copy constructor of the class.
  ClippingFilm (const ClippingFilm& film) = default;

  //! The move constructor of the class.
  ClippingFilm (ClippingFilm&& film) = default;

  //! The default class destructor.
  virtual ~ClippingFilm () = default;

  //! The copy assignment operator of the class.
  auto operator = (const ClippingFilm& film) -> ClippingFilm& = default;

  //! The move assignment operator of the class.
  auto operator = (ClippingFilm&& film) -> ClippingFilm& = default;

  /*!
   * @fn operator () (uint32_t x, uint32_t y) const -> Pixel;
   * @brief 
   * @details 
   * @return Copy data of pixel
   * @exception std::out_of_range
   */
  auto operator () (uint32_t x, uint32_t y) const -> Pixel;

  /*!
   * @fn operator () (uint32_t x, uint32_t y) -> Pixel&;
   * @brief 
   * @details 
   * @return Referenced pixel data
   * @exception std::out_of_range
   */
  auto operator () (uint32_t x, uint32_t y) -> Pixel&;

public:
  //! @fn Bounds2ui GetFilmCoordinates ()
  //! @brief 
  //! @return Area of clipping film.
  //! @exception none
  //! @details 
  auto Bounds2 () const -> Bounds2ui;

private:
  Bounds2ui area_;
  Image     film_;
}; // class ClippingFilm
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CLIPPING_FILM_H_
