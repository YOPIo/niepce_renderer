#ifndef _IBL_H_
#define _IBL_H_

#include "light.h"
#include "../core/image.h"

namespace niepce
{

class Ibl : public Light
{
  /* Ibl constructors */
public:
  Ibl ();
  Ibl (const std::string& filepath);


  /* Ibl destructor */
public:
  virtual ~Ibl ();


  /* Ibl public operators*/
public:
  Ibl (const Ibl&  ibl) = default;
  Ibl (      Ibl&& ibl) = default;

  auto operator = (const Ibl&  ibl) -> Ibl& = default;
  auto operator = (      Ibl&& ibl) -> Ibl& = default;


  /* Light public interface */
public:
  auto Emission
  (
   const Ray& ray
  )
  const -> Spectrum;

  auto Load (const std::string& filepath) -> void;


  /* Light private data */
private:
  Image image_;

}; // class Ibl


}  // namespace niepce

#endif // _IBL_H_
