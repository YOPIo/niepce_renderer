#ifndef _TEXTURE_H_
#define _TEXTURE_H_

#include "../core/niepce.h"
#include "../core/interaction.h"

namespace niepce
{


template <typename T>
class Texture
{
 public:
  /* Constructors */
  Texture ();
  virtual ~Texture ();

  Texture (const Texture&  texture) = default;
  Texture (      Texture&& texture) = default;

  /* Operators */
  auto operator = (const Texture&  texture) -> Texture& = default;
  auto operator = (      Texture&& texture) -> Texture& = default;

  /* Interface */
 public:
  virtual auto Evaluate (const SurfaceInteraction& interaction) const -> T = 0;
}; // class Texture


}  // namespace niepce

#endif // _TEXTURE_H_
