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
#include "bounds2f.h"
#include "imageio.h"
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
   unsigned int width,   // Resolution
   unsigned int height,  // Resolution
   Float        diagonal // Physical length (mm)
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
   * @fn Bounds2f PhysicalBounds ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto PhysicalBounds () const noexcept -> Bounds2f;

  /*!
   * @fn Bounds2f RenderingBounds ()
   * @brief Return the bound of rendering area.
   * @return 
   * @exception none
   * @details
   */
  auto RenderingBounds () const noexcept -> Bounds2f;

  /*!
   * @fn Bounds2f Resolution ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Resolution () const noexcept -> Bounds2f;

  /*!
   * @fn void Save ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Save () const noexcept -> void;

  /*!
   * @fn void SaveAs (const)
   * @brief 
   * @param[in] filename
   *   
   * @return 
   * @exception none
   * @details
   */
  auto SaveAs (const char* filename) const noexcept -> void;

  /*!
   * @fn void SetFilmTile (const)
   * @brief 
   * @param[in] tile
   *    t
   * @return 
   * @exception none
   * @details
   */
  auto AddFilmTile (const FilmTile& tile) noexcept -> void;

private:
  //! @brief filename
  std::string filename_;

  //! @brief <width, heigth>
  const Bounds2f resolution_;

  //! @brief Physical length of diagonal. [m]
  const Float diagonal_;

  //! @brief
  std::vector <FilmTile> tiles_;
}; // class Film
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_

