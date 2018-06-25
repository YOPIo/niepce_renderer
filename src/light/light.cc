/*!
 * @file light.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "light.h"
#include "infinite_light.h"
#include "../core/attributes.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
Light::Light ()
{}
/*
// ---------------------------------------------------------------------------
*/
auto CreateLight (const Attributes& attributes) -> std::shared_ptr <Light>
{
  // Get type as string.
  const auto type = attributes.FindString ("type");
  if (type == "infinite")
  {
    return CreateInfiniteLight (attributes);
  }
  std::cerr << "Could not create light." << std::endl;
  return nullptr;
}
/*
// ---------------------------------------------------------------------------
*/
} // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
