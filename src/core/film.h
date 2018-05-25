/*!
 * @file film.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _FILM_H_
#define _FILM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
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
  Film () = delete;

  //! The constructor takes a resolution, physical length of diagonal.
  Film
  (
   const char*  filename,
   unsigned int width,
   unsigned int height,
   Float        diagonal
  );

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
  /*!
   * @fn Float Diagonal ()
   * @brief Return the physical length of diagonal.
   * @return 
   * @exception none
   * @details 
  */
  auto Diagonal () const noexcept -> Float;

  /*!
   * @fn unsigned Height () const noexcept
   * @brief Return the resolution of height.
   * @return 
   * @exception none
   * @details 
   */
  auto Height () const noexcept -> unsigned int;

  /*!
   * @fn unsigned Width () const noexcept
   * @brief Return the resolution of width.
   * @return 
   * @exception none
   * @details 
  */
  auto Width () const noexcept -> unsigned int;

private:
  //! @brief filename
  std::string filename_;

  //! @brief <width, heigth>
  const std::pair <unsigned int, unsigned int> resolution_;

  //! @brief Physical length of diagonal. [m]
  const Float diagonal_;

}; // class Film
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_

