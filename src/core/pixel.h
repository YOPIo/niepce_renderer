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

  //! The copy constructor of the class.
  Pixel (const Pixel& pixel) = default;

  //! The move constructor of the class.
  Pixel (Pixel&& pixel) = default;

  //! The default class destructor.
  virtual ~Pixel () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Pixel& pixel) -> Pixel& = default;

  //! The move assignment operator of the class.
  auto operator = (Pixel&& pixel) -> Pixel& = default;

public:
  //! @fn Float GetR ()
  //! @brief Return red component
  //! @return Float [0,1]
  //! @exception none
  auto GetR () const -> Float;

  //! @fn Float GetG ()
  //! @brief Return green component
  //! @return Float [0,1]
  //! @exception none
  auto GetG () const -> Float;

  //! @fn Float GetB ()
  //! @brief Return blue component
  //! @return Float [0,1]
  //! @exception none
  auto GetB () const -> Float;


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
    std::array <Float, 3> rgb_;
    struct { Float r_, g_, b_; };
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

