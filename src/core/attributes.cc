/*!
 * @file attributes.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "attributes.h"
#include "vector3f.h"
#include "point3f.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddBool (const std::string& name, bool value) -> void
{
  bools_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddInt (const std::string& name, int value) -> void
{
  ints_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddFloat (const std::string& name, Float value) -> void
{
  floats_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddString (const std::string& name, const std::string& value)
  -> void
{
  strings_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddVector3f (const std::string& name, const Vector3f& value)
  -> void
{
  vector3fs_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddPoint3f (const std::string& name, const Point3f& value)
  -> void
{
  point3fs_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::AddSpectrum (const std::string& name, const Spectrum& value)
  -> void
{
  spectrums_.emplace (name, value);
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindBool (const std::string& name) const -> bool
{
  try { return bools_.at (name); }
  catch (const std::exception& e) { return false; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindInt (const std::string& name) const -> int
{
  try { return ints_.at (name); }
  catch (const std::exception& e) { return 0; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindFloat (const std::string& name) const -> Float
{
  try { return floats_.at (name); }
  catch (const std::exception& e) { return 0; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindString (const std::string& name) const -> std::string
{
  try { return strings_.at (name); }
  catch (const std::exception& e) { return ""; }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindVector3f (const std::string& name) const -> Vector3f
{
  try { return vector3fs_.at (name); }
  catch (const std::exception& e) { return Vector3f::Zero (); }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindPoint3f (const std::string& name) const -> Point3f
{
  try { return point3fs_.at (name); }
  catch (const std::exception& e) { return Point3f::Zero(); }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::FindSpectrum (const std::string& name) const -> Spectrum
{
  try { return spectrums_.at (name); }
  catch (const std::exception& e) { return Spectrum::Zero (); }
}
/*
// ---------------------------------------------------------------------------
*/
auto Attributes::Clear () -> void
{
  bools_.clear ();
  ints_.clear ();
  floats_.clear ();
  strings_.clear ();
  vector3fs_.clear ();
  point3fs_.clear ();
  spectrums_.clear ();
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
