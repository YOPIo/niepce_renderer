/*!
 * @file camera.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "camera.h"
#include "pinhole.h"
#include "realistic_camera.h"
#include "../core/attributes.h"
#include "../core/bounds2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Camera::Camera
(
 const Transform& t,
 const char* filename,
 unsigned int width,
 unsigned int height,
 Float diagonal
) :
  Film (filename, width, height, diagonal),
  camera_to_world_ (t)
{}
/*
// ---------------------------------------------------------------------------
*/
auto CreateCamera (const Attributes& attributes) -> std::shared_ptr <Camera>
{
  const std::string type = attributes.FindString ("type");
  if (type == "pinhole")
  {
    return CreatePinholeCamera (attributes);
  }
  if (type == "realistic")
  {
    // Create realistic camera
  }
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
