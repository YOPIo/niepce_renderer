#include "image_map.h"

namespace niepce
{

ImageMapTexture::ImageMapTexture (const std::string& filepath) :
  Texture<Vector4f>()
{
  map_.Load (filepath);
}

ImageMapTexture::~ImageMapTexture ()
{}

auto ImageMapTexture::Evaluate (const SurfaceInteraction &si) const -> Spectrum
{
  return map_ (si.texcoord);
}


}  // namespace niepce
