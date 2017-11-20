#include "image.h"
/*
// ---------------------------------------------------------------------------
*/
#define STB_IMAGE_IMPLEMENTATION
#include "../ext/stb_image.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Image::Image ()
{}
/*
// ---------------------------------------------------------------------------
*/
Image::Image (const std::string& filepath)
{
  Load (filepath);
}
/*
// ---------------------------------------------------------------------------
*/
Image::~Image ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto Image::operator () (const Point2i &uv) const -> Vector4f
{
  const Vector4f s = image_[uv.u * resolution_[0] + uv.v];
  return Vector4f (s.x, s.y, s.z, s.w);
}
/*
// ---------------------------------------------------------------------------
*/
auto Image::operator () (const Point2f &uv) const -> Vector4f
{
  if (!image_)
  {
    return Spectrum::Zero ();
  }

  // uv must be [0, 1]
  // Dicide texel position
  const Point2i texel (static_cast<int> (uv.u * resolution_[0]),
                       static_cast<int> (uv.v * resolution_[1]));

  // Get texel
  std::size_t idx = texel[1] * resolution_[0] + texel[0];

  if (idx >= resolution_[0] * resolution_[1])
  {
    idx = 0;
  }

  return image_[idx];
}
/*
// ---------------------------------------------------------------------------
*/
auto Image::Load (const std::string& filepath) -> bool
{
  // Get file extension
  const std::string ext = GetFileExtension (filepath);

  if (ext == ".png" || ext == ".jpeg" || ext == ".bmp")
  {
    // Update filepath
    filepath_ = filepath;
    image_.reset (LoadImage (filepath, &resolution_.x, &resolution_.y));
    return true;
  }
  if (ext == ".hdr")
  {
    // Update filepath
    filepath_ = filepath;
    image_.reset (LoadHdrImage (filepath, &resolution_.x, &resolution_.y));
    return true;
  }

  return false;
}
/*
// ---------------------------------------------------------------------------
*/
auto LoadImage
(
 const std::string& filepath,
 uint32_t*          width,
 uint32_t*          height
)
-> Vector4f*
{
  int x, y, n;
  unsigned char* data = stbi_load (filepath.c_str (), &x, &y, &n, 4);

  // Allocate memory
  Vector4f* ret = new Vector4f [x * y];

  // Copy data
  *width  = static_cast<uint32_t> (x);
  *height = static_cast<uint32_t> (y);
  for (std::size_t i = 0; i < x * y; ++i)
  {
    const Float r = static_cast<Float> (data[4 * i + 0]) / 255.0;
    const Float g = static_cast<Float> (data[4 * i + 1]) / 255.0;
    const Float b = static_cast<Float> (data[4 * i + 2]) / 255.0;
    const Float a = static_cast<Float> (data[4 * i + 3]) / 255.0;
    ret[i] = Vector4f (r, g, b, a);
  }

  // Free original data
  stbi_image_free (data);

  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
auto LoadHdrImage
(
 const std::string& filepath,
 uint32_t*          width,
 uint32_t*          height
)
-> Vector4f*
{

  stbi_hdr_to_ldr_gamma(2.2f);
  stbi_hdr_to_ldr_scale(1.0f);

  int x, y, n;
  float* data = stbi_loadf(filepath.c_str (), &x, &y, &n, 4);

  // Allocate memory
  Vector4f* ret = new Vector4f[x * y];

  // Copy data
  *width  = static_cast<uint32_t> (x);
  *height = static_cast<uint32_t> (y);
  for (std::size_t i = 0; i < x * y; ++i)
  {
    ret[i] = Vector4f (data[4 * i + 0], data[4 * i + 1], data[4 * i + 2], data[4 * i + 3]);
  }

  // Free original image
  stbi_image_free (data);

  return ret;
}
/*
// ---------------------------------------------------------------------------
*/
template <typename DataType>
auto CreateBaseImage (uint32_t width, uint32_t height)
  -> ImagePtr <Pixel <DataType>>
{
  ImagePtr <Pixel <DataType>> res
    (new BaseImage <Pixel <DataType>> [width * height],
     std::default_delete <BaseImage <Pixel <DataType>> []> ());
  return std::move (res);
}
/*
// ---------------------------------------------------------------------------
*/
template
auto CreateBaseImage (uint32_t width, uint32_t height)
  -> ImagePtr <Pixel <Spectrum>>;
/*
// ---------------------------------------------------------------------------
*/
template
auto CreateBaseImage (uint32_t width, uint32_t height)
  -> ImagePtr <Pixel <Float>>;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
