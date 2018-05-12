/*!
 * @file pixel.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#ifndef _PIXEL_H_
#define _PIXEL_H_
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
//! @class Pixel
//! @brief RGB color space [0, 1]
//! @details
//! ----------------------------------------------------------------------------
class Pixel
{
public:
  //! The default class constructor.
  Pixel () = default;

  //! The constructor initialize the pixel by RGB format.
  Pixel (Float r, Float g, Float b);

  //! The copy constructor of the class.
  Pixel (const Pixel& pixel) = default;

  //! The move constructor of the class.o
  Pixel (Pixel&& pixel) = default;

  //! The default class destructor.
  virtual ~Pixel () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Pixel& pixel) -> Pixel& = default;

  //! The move assignment operator of the class.
  auto operator = (Pixel&& pixel) -> Pixel& = default;

public:
  //! @fn Float R ()
  //! @brief Return red component
  //! @return Float [0,1]
  //! @exception none
  auto R () const -> Float;

  //! @fn Float G ()
  //! @brief Return green component
  //! @return Float [0,1]
  //! @exception none
  auto G () const -> Float;

  //! @fn Float B ()
  //! @brief Return blue component
  //! @return Float [0,1]
  //! @exception none
  auto B () const -> Float;


  //! @fn void SetR (Float)
  //! @param[in] Float red [0, 1]
  //! @brief Set red component
  //! @return void
  //! @exception none
  auto SetR (Float r) -> void;

  //! @fn void SetG (Float green)
  //! @param[in] Float green [0, 1]
  //! @brief Set green component
  //! @return void
  //! @exception none
  auto SetG (Float g) -> void;

  //! @fn void SetB (Float blue)
  //! @param[in] Float blue [0, 1]
  //! @brief Set blue component
  //! @return void
  //! @exception none
  auto SetB (Float b) -> void;

private:
  union
  {
    std::array <Float, 4> rgba_;
    struct { Float r_, g_, b_, a_; };
  };
}; // class Pixel
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _PIXEL_H_

