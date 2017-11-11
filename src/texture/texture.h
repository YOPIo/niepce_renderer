#ifndef _TEXTURE_H_
#define _TEXTURE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/geometry.h"
#include "../core/interaction.h"
#include "../core/object.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
template <typename ReturnType>
class Texture : public Object
{
  /* Texture public constructors */
public:
  Texture ();


  /* Texture public destructor */
  virtual ~Texture () = default;

  Texture (const Texture&  texture) = default;
  Texture (      Texture&& texture) = default;


  /* Texture public operators */
public:
  auto operator = (const Texture&  texture) -> Texture& = default;
  auto operator = (      Texture&& texture) -> Texture& = default;


  /* Texture public interface */
public:
  virtual auto Evaluate (const SurfaceInteraction& si) const -> ReturnType = 0;

  virtual auto ToString () const -> std::string = 0;

}; // class Texture
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _TEXTURE_H_
