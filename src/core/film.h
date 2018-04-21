/*!
 * @file film.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/21
 * @details 
 */
#ifndef _FILM_H_
#define _FILM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Film
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Film
{
public:
  //! The default class constructor.
  Film () = default;

  //! The constructor of the class.
  /*!
   * Initialize size of film and image with arguments.
   */
  Film (uint32_t width, uint32_t height);

  //! The copy constructor of the class.
  Film (const Film& film) = default;

  //! The move constructor of the class.
  Film (Film&& film) = default;

  //! The default class destructor.
  virtual ~Film () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Film& film) -> Film& = default;

  //! The move assignment operator of the class.
  auto operator = (Film&& film) -> Film& = default;

public:
  //! @fn void OverrideWithClippingFilm (const)
  //! @brief 
  //! @param[in] ClippingFilm
  //! @return 
  //! @exception none
  //! @details 
  auto OverrideWithClippingFilm (const ClippingFilm& film) -> void;

private:
  const std::pair <uint32_t, uint32_t> resolution_;
  Image film_;
}; // class Film
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_
