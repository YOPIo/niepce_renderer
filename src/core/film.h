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
/*
// ---------------------------------------------------------------------------
*/
auto Denoising   (Film *film) -> void;
auto ToneMapping (Film *film) -> void;
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
   Float        diagonal // Physical length [m]
  );

  //! The copy constructor of the class.
  Film (const Film& film);

  //! The move constructor of the class.
  Film (Film&& film);

  //! The default class destructor.
  virtual ~Film () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Film& film) -> Film& = default;

  //! The move assignment operator of the class.
  auto operator = (Film&& film) -> Film& = default;

public:
  auto Width  () const noexcept -> int { return bounds_.Width (); };
  auto Height () const noexcept -> int { return bounds_.Height (); };

  auto SaveAs (const char *filename) const noexcept -> void;

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
   * @fn Bounds2f Resolution ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto Resolution () const noexcept -> Bounds2f;

  /*!
   * @fn void SetFilmTile (const)
   * @brief 
   * @param[in] tile
   * @return 
   * @exception none
   * @details
   */
  auto ReplaceFilmTile (const FilmTile& tile) noexcept -> void;

  /*!
   * @fn void UpdateFilmTile (const)
   * @brief 
   * @param[in] tile
   * @return 
   * @exception none
   * @details
   */
  auto UpdateFilmTile (const FilmTile &tile) noexcept -> void;

private:
  //! @brief
  const Bounds2f bounds_;

  //! @brief Physical length of diagonal. [m]
  const Float diagonal_;

public:
  std::unique_ptr <Spectrum []> data_;
}; // class Film
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FILM_H_

