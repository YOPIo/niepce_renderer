/*!
 * @file attributes.h
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#ifndef _ATTRIBUTES_H_
#define _ATTRIBUTES_H_
/*
// ---------------------------------------------------------------------------
*/
#include "niepce.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
//! ----------------------------------------------------------------------------
//! @class Attributes
//! @brief
//! @details
//! ----------------------------------------------------------------------------
class Attributes
{
  typedef std::shared_ptr <Texture> TexturePtr;

public:
  //! The default class constructor.
  Attributes () = default;

  //! The copy constructor of the class.
  Attributes (const Attributes& attributes) = default;

  //! The move constructor of the class.
  Attributes (Attributes&& attributes) = default;

  //! The default class destructor.
  virtual ~Attributes () = default;

  //! The copy assignment operator of the class.
  auto operator = (const Attributes& attributes) -> Attributes& = default;

  //! The move assignment operator of the class.
  auto operator = (Attributes&& attributes) -> Attributes& = default;

public:
  auto AddBool     (const std::string& name, bool value) -> void;
  auto AddInt      (const std::string& name, int value) -> void;
  auto AddFloat    (const std::string& name, Float value) -> void;
  auto AddString   (const std::string& name, const std::string& value) -> void;
  auto AddVector3f (const std::string& name, const Vector3f& value) -> void;
  auto AddPoint3f  (const std::string& name, const Point3f& value) -> void;
  auto AddSpectrum (const std::string& name, const Spectrum& value) -> void;

  auto FindBool     (const std::string& name) const -> bool;
  auto FindInt      (const std::string& name) const -> int;
  auto FindFloat    (const std::string& name) const -> Float;
  auto FindString   (const std::string& name) const -> std::string;
  auto FindVector3f (const std::string& name) const -> Vector3f;
  auto FindPoint3f  (const std::string& name) const -> Point3f;
  auto FindSpectrum (const std::string& name) const -> Spectrum;

  auto Clear () -> void;

private:
  std::map <std::string, bool>        bools_;
  std::map <std::string, int>         ints_;
  std::map <std::string, Float>       floats_;
  std::map <std::string, std::string> strings_;
  std::map <std::string, Vector3f>    vector3fs_;
  std::map <std::string, Point3f>     point3fs_;
  std::map <std::string, Spectrum>    spectrums_;
}; // class Attributes
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _ATTRIBUTES_H_

