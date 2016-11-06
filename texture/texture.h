#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "image.h"

namespace niepce
{

class Texture
{
 public:
  Texture();
  virtual ~Texture();

  Texture(const Texture& texture) = default;
  Texture(Texture&& texture)      = default;
  Texture& operator = (const Texture& texture) = default;
  Texture& operator = (Texture&& texture)      = default;
};


} // namespace niepce


#endif // _TEXTURE_H_
