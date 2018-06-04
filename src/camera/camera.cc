/*!
 * @file camera.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "camera.h"
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
}  // namespace niepce
