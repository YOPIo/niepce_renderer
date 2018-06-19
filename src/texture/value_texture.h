/*!
 * @file value_texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _VALUE_TEXTURE_H_
#define _VALUE_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
#include "../core/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class ValueTexture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class ValueTexture : public Texture
{
public:
  //! The default class constructor.
  ValueTexture () = default;

  //! The constructor takes filename.
  ValueTexture (const Vector3f& value);

  //! The copy constructor of the class.
  ValueTexture (const ValueTexture& texture) = default;

  //! The move constructor of the class.
  ValueTexture (ValueTexture&& texture) = default;

  //! The default class destructor.
  virtual ~ValueTexture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const ValueTexture& texture) -> ValueTexture& = default;

  //! The move assignment operator of the class.
  auto operator = (ValueTexture&& texture) -> ValueTexture& = default;

public:
  /*!
   * @fn Pixel Sample (Float)
   * @brief Sample the pixel.
   * @param[in] uv
   *    UV-parameter [0, 1]
   * @return Pixel
   * @exception none
   * @details
   */
  auto Sample (const Point2f& uv) const noexcept -> Vector3f override final;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto IsBlack () const noexcept -> bool override final;

private:
  Vector3f value_;
}; // class ValueTexture
/*
// ---------------------------------------------------------------------------
// Function for the value texture.
// ---------------------------------------------------------------------------
*/
auto CreateValueTexture (const Vector3f& value) -> Texture*;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VALUE_TEXTURE_H_

