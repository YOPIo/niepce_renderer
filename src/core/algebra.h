#ifndef _ALGEBRA_H_
#define _ALGEBRA_H_
/*
// ---------------------------------------------------------------------------
*/
#include <cmath>
#include <string>
#include <array>
/*
// ---------------------------------------------------------------------------
// SIMD
// ---------------------------------------------------------------------------
*/
#if defined (CLANG)
  #include <x86intrin.h>
#else
  #include <mmintrin.h>
  #include <xmmintrin.h>
// #include <intrin.h> // MSVC
#endif
/*
// ---------------------------------------------------------------------------
*/
#define ALIGN(n) alignas((n))
#define ALIGN16  alignas(16)
#define ALIGN32  alignas(32)
#define ALIGN64  alignas(64)
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
#if defined (NI_FLOAT_IS_DOUBLE)
typedef double Float;
#define SIMD_ALIGN 32
#else
typedef float Float;
#define SIMD_ALIGN 16
#endif
typedef unsigned Index;
/*
// ---------------------------------------------------------------------------
// Tiny obj loader option
// ---------------------------------------------------------------------------
*/
#if defined (NI_FLOAT_IS_DOUBLE)
#define TINYOBJLOBJLOADER_USE_DOUBLE
#endif
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _ALGEBRA_H_
