/*!
 * @file material.h
 * @brief 
 * @author Masashi Yoshida
 * @date 2018/5/5
 * @details 
 */
#ifndef _MATERIAL_H_
#define _MATERIAL_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include "../math/vector3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Material
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Material
{
public:
  enum Type
  {
    kDiffuse,
    kSpecular,
    kRefraction
  };

public:
  //! The default class constructor.
  Material () = default;

  //! The copy constructor of the class.
  Material (const Material& material) = default;

  //! The move constructor of the class.
  Material (Material&& material) = default;

  //! The default class destructor.
  virtual ~Material () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Material& material) -> Material& = default;

  //! The move assignment operator of the class.
  auto operator = (Material&& material) -> Material& = default;

public:
  Vector3f emittion, color;
}; // class Material
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _MATERIAL_H_
