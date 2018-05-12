/*!
 * @file texture.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _TEXTURE_H_
#define _TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/ioimage.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
//! ----------------------------------------------------------------------------
//! @class Texture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Texture
{
public:
  //! The default class constructor.
  Texture () = default;

  //! The constructor takes filename.
  Texture (const char* filename);

  //! The copy constructor of the class.
  Texture (const Texture& texture) = default;

  //! The move constructor of the class.
  Texture (Texture&& texture) = default;

  //! The default class destructor.
  virtual ~Texture () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Texture& texture) -> Texture& = default;

  //! The move assignment operator of the class.
  auto operator = (Texture&& texture) -> Texture& = default;

public:
  /*!
   * @fn operator ()
   * @brief Return the pixel value.
   * @details 
   * @param [in] x component
   * @param [in] y component
   * @return Pixel
   * @exception none
   */
  auto operator () (unsigned int x, unsigned int y) const noexcept -> Pixel;

  /*!
   * @fn operator ()
   * @brief 
   * @details 
   * @param [in] u [0, 1]
   * @param [in] v [0, 1]
   * @return 
   * @exception none
   */
  virtual auto operator () (Float u, Float v) const noexcept -> Pixel;

public:
  /*!
   * @fn Pixel At (unsigned)
   * @brief Return the pixel.
   * @param[in] x
   * @param[in] y
   * @return 
   * @exception std::out_of_range if index over the range.
   * @details
   */
  auto At (unsigned int x, unsigned int y) const -> Pixel;

  /*!
   * @fn Pixel At (Float)
   * @brief 
   * @param[in] 
   * @param[out] 
   * @return 
   * @exception none
   * @details
   */
  virtual auto At (Float u, Float v) const -> Pixel;

private:
  std::shared_ptr <IOImage> image_;
}; // class Texture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_H_

