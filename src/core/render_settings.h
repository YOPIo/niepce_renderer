#ifndef _RENDER_SETTINGS_H_
#define _RENDER_SETTINGS_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
#include "geometry.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct RenderSettings
{
  RenderSettings();
  virtual ~RenderSettings();

  RenderSettings(const RenderSettings&  settings) = default;
  RenderSettings(      RenderSettings&& settings) = default;

  auto operator = (const RenderSettings&  settings) -> RenderSettings& = default;
  auto operator = (      RenderSettings&& settings) -> RenderSettings& = default;

  // RenderSettings data
  // Size of rendering image
  std::pair <uint32_t, uint32_t> resolution;

  // Samples per pixel
  uint16_t samples;
  // Super samples per pixel
  uint16_t super_samples;
};
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _RENDER_SETTINGS_H_
