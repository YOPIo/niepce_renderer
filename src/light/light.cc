/*!
 * @file light.cc
 * @brief 
 * @author Masashi Yoshida
 * @date 
 * @details 
 */
#include "light.h"
#include "infinite_light.h"
#include "area_light.h"
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
auto CreateLight
(
 const LightType&  type,
 const Attributes& attributes
)
  -> std::shared_ptr <Light>
{
  if (type == niepce::LightType::kInfiniteLight)
  {
    std::cerr << "create infinite light" << std::endl;
    return CreateInfiniteLight (attributes);
  }
  if (type == niepce::LightType::kAreaLight)
  {
    std::cerr << "create area light" << std::endl;
    return CreateAreaLight (attributes);
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
