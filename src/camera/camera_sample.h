/*!
 * @file camera_sample.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _CAMERA_SAMPLE_H_
#define _CAMERA_SAMPLE_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../core/point2f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
struct CameraSample
{
  CameraSample
  (
   const Point2f& film,
   const Point2f& lens
  ) :
    film_ (film),
    lens_ (lens)
  {}

  Point2f film_; // Pixel position
  Point2f lens_; // (-1, 1)^2
};
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _CAMERA_SAMPLE_H_
