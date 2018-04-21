/*!
 * @file niepce.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/4/20
 * @details 
 */
#ifndef _NIEPCE_H_
#define _NIEPCE_H_
/*
// ---------------------------------------------------------------------------
// Niepce renderer std includes
// ---------------------------------------------------------------------------
*/
#include <array>
#include <cmath>
#include <cstdint>
#include <memory>
#include <string>
/*!
 * @namespace niepce
 */
namespace niepce
{
/*
// ---------------------------------------------------------------------------
// Forward class, struct and enum declaration
// ---------------------------------------------------------------------------
*/
template <typename T> class Bounds2;
class ClippingFilm;
class Film;
class Image;
class Pixel;
// class Point2;
// class Point3;
// class Status; 
class Vector2f;
class Vector3f;
/*
// ---------------------------------------------------------------------------
// Niepce renderer typedefs
// ---------------------------------------------------------------------------
*/
/*!
 * @typedef
 * @brief Choose float or double
 */
typedef float Float;
/*!
 * @typedef Bounds2i
 * @brief 
 */
typedef Bounds2<uint32_t> Bounds2ui;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _NIEPCE_H_

