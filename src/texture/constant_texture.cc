#include "constant_texture.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
ConstantTexture<ReturnType>::ConstantTexture ()
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
ConstantTexture<ReturnType>::ConstantTexture (const ReturnType& value) :
    value_ (value)
{}
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
auto ConstantTexture<ReturnType>::Evaluate (const SurfaceInteraction& si) const -> ReturnType
{
  return value_;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
auto ConstantTexture <ReturnType>::ToString () const -> std::string
{
  return std::string ();
}
/*
// ---------------------------------------------------------------------------
*/
template class ConstantTexture<Spectrum>;
template class ConstantTexture<Float>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
