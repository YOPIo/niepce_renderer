#ifndef _EFLOAT_H_
#define _EFLOAT_H_

#include "niepce.h"

namespace niepce
{

class EFloat
{
 public:
  EFloat();
  EFloat(Float v, Float err = 0.f);
  virtual ~EFloat();

  EFloat(const EFloat& arg) = default;
  EFloat(EFloat&& arg)      = default;

  auto operator = (const EFloat& arg) -> EFloat& = default;
  auto operator = (EFloat&& arg)      -> EFloat& = default;

  /*
    Operation for basic arithmetic operations
   */
  auto operator + (const EFloat& f) const -> EFloat;
  auto operator - (const EFloat& f) const -> EFloat;
  auto operator * (const EFloat& f) const -> EFloat;
  auto operator / (const EFloat& f) const -> EFloat;

  /*
    Cast to 'float' or 'double'
   */
  operator float  () const;
  operator double () const;

 private:
  Float v_;
  Float err_; // Absolute error bounds.
};


} // namespace niepce

#endif // _EFLOAT_H_
