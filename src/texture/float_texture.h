/*!
 * @file float_texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _FLOAT_TEXTURE_H_
#define _FLOAT_TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class FloatTexture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class FloatTexture : public Texture
{
public:
  //! The default class constructor.
  FloatTexture () = delete;

  //! The constructor takes Float.
  FloatTexture (Float value);

  //! The copy constructor of the class.
  FloatTexture (const FloatTexture& texture) = default;

  //! The move constructor of the class.
  FloatTexture (FloatTexture&& texture) = default;

  //! The default class destructor.
  virtual ~FloatTexture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const FloatTexture& texture) -> FloatTexture& = default;

  //! The move assignment operator of the class.
  auto operator = (FloatTexture&& texture) -> FloatTexture& = default;

public:
  /*!
   * @fn Spectrum Sample (const)
   * @brief 
   * @param[in] uv
   * @return 
   * @exception none
   * @details 
   */
  auto Sample (const Point2f& uv) const noexcept -> Spectrum override final;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details 
   */
  auto IsBlack () const noexcept -> bool override final;

private:
  const Float value_;

}; // class FloatTexture
/*
// ---------------------------------------------------------------------------
*/
auto CreateFloatTexture (Float value) -> std::shared_ptr <Texture>;
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _FLOAT_TEXTURE_H_
