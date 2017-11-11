#ifndef _IMAGE_MAP_TEXTURE_H_
#define _IMAGE_MAP_TEXTURE_H_

#include "texture.h"
#include "../core/image.h"

namespace niepce
{

class ImageMapTexture : public Texture<Vector4f>
{
  /* ImageMapTexture constructors */
public:
  ImageMapTexture () = delete;
  ImageMapTexture (const std::string& filepath);


  /* ImageMapTexture destructor */
public:
  virtual ~ImageMapTexture ();


  /* ImageMapTexture public operators*/
public:
  ImageMapTexture (const ImageMapTexture&  tex) = default;
  ImageMapTexture (      ImageMapTexture&& tex) = default;

  auto operator = (const ImageMapTexture&  tex) -> ImageMapTexture& = default;
  auto operator = (      ImageMapTexture&& tex) -> ImageMapTexture& = default;

  auto operator [] (std::size_t idx) -> Vector3f
  {
    return Vector3f(map_[idx].x, map_[idx].y, map_[idx].z);
  }


  /* ImageMapTexture public data */
public:
  auto Evaluate (const SurfaceInteraction& si) const -> Vector4f override final;

  auto ToString () const -> std::string override final;


  /* ImageMapTexture private data */
private:
  Image map_;

}; // class ImageMapTexture

}  // namespace niepce

#endif // _IMAGE_MAP_TEXTURE_H_
