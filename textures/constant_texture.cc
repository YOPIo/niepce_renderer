#include "constant_texture.h"

namespace niepce
{

template <typename T>
ConstantTexture<T>::ConstantTexture ()
{}

template <typename T>
ConstantTexture<T>::~ConstantTexture ()
{}

template <typename T>
auto ConstantTexture<T>::Evaluate (const SurfaceInteraction& interaction) const -> T
{
  return value_;
}

}  // namespace niepce
