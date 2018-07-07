/*!
 * @file texture.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "value_texture.h"
#include "../core/vector3f.h"
#include "../core/pixel.h"
#include "../core/attributes.h"
#include "../core/material_attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
ValueTexture<T>::ValueTexture (const T& value) :
  value_ (value)
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ValueTexture<T>::Evaluate (const Intersection& isect) const noexcept -> T
{
  return value_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename T>
auto ValueTexture<T>::IsBlack () const noexcept -> bool
{
  if (value_ == T (0)){ return true; }
  return false;
}
/*
// ---------------------------------------------------------------------------
// Function for the value texture.
// ---------------------------------------------------------------------------
*/
template <typename T>
auto CreateValueTexture (const T &value) -> std::shared_ptr <Texture <T>>
{
  return std::make_shared <ValueTexture <T>> (value);
}
/*
// ---------------------------------------------------------------------------
*/
template class ValueTexture <Float>;
template class ValueTexture <Spectrum>;

template auto CreateValueTexture <Float> (const Float &)
  -> std::shared_ptr <Texture <Float>>;
template auto CreateValueTexture <Spectrum> (const Spectrum &)
  -> std::shared_ptr <Texture <Spectrum>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
