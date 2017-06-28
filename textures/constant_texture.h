#ifndef _CONSTANT_TEXTURE_H_
#define _CONSTANT_TEXTURE_H_

#include "texture.h"

namespace niepce
{

template <typename T>
class ConstantTexture : public Texture<T>
{
 public:
  /* Constructors */
  ConstantTexture ();
  virtual ~ConstantTexture ();

  ConstantTexture (const ConstantTexture&  texture) = default;
  ConstantTexture (      ConstantTexture&& texture) = default;


  /* Operators*/
  auto operator = (const ConstantTexture&  texture) -> ConstantTexture& = default;
  auto operator = (      ConstantTexture&& texture) -> ConstantTexture& = default;


  /* Methods  */
 public:
  auto Evaluate (const SurfaceInteraction& interaction) const -> T;


  /* Data */
 private:
  T value_;

}; // class ConstantTexture


}  // namespace niepce

#endif // _CONSTANT_TEXTURE_H_
