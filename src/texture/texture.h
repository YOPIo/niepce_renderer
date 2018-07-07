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
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
enum class TextureType : uint8_t
{
 kValueFloat,
 kValueSpectrum,
 kImageFloat,
 kImageSpectrum,
 kUnknown
};
//! ----------------------------------------------------------------------------
//! @class Texture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
template <typename T>
class Texture
{
public:
  //! The default class constructor.
  Texture () = default;

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
   * @fn T Evaluate (const Intersection &)
   * @brief 
   * @param[in] isect
   * @return 
   * @exception none
   * @details 
   */
  virtual auto Evaluate (const Intersection &isect) const noexcept -> T = 0;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  virtual auto IsBlack () const noexcept -> bool = 0;
}; // class Texture
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateTexture
(
 const Attributes &attrs
)
-> std::shared_ptr <Texture <T>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_H_
