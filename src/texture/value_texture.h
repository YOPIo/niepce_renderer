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
//! ----------------------------------------------------------------------------
//! @class ValueTexture
//! @brief
//! @details
//! ----------------------------------------------------------------------------
template <typename T>
class ValueTexture : public Texture <T>
{
public:
  //! The default class constructor.
  ValueTexture () = default;

  //! The constructor takes filename.
  ValueTexture (const T& value);

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
   * @fn T Evaluate (const)
   * @brief 
   * @param[in] isect
   * @return 
   * @exception none
   * @details 
   */
  auto Evaluate (const Intersection &isect) const noexcept -> T override final;

  /*!
   * @fn bool IsBlack ()
   * @brief 
   * @return 
   * @exception none
   * @details
   */
  auto IsBlack () const noexcept -> bool override final;

private:
  const T value_;
}; // class ValueTexture
/*
// ---------------------------------------------------------------------------
// Function for the value texture.
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateValueTexture (const T& valu) -> std::shared_ptr <Texture <T>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _VALUE_TEXTURE_H_

