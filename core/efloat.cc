#include "efloat.h"

namespace niepce
{

EFloat::EFloat()
{}

EFloat::EFloat(Float v, Float err) :
    v_(v), err_(err)
{}

EFloat::~EFloat()
{}

auto EFloat::operator + (const EFloat& f) const -> EFloat
{
  EFloat res;
  res.v_   = v_ + f.v_;
  res.err_ = err_ + f.err_;
  return res;
}

auto EFloat::operator - (const EFloat& f) const -> EFloat
{
  EFloat res;
  res.v_   = v_ - f.v_;
  res.err_ = err_ + f.err_;
  return res;
}

auto EFloat::operator * (const EFloat& f) const -> EFloat
{
  // ほんとに正しい？
  // http://physnotes.jp/foundations/er_p4/
  EFloat res;
  res.v_   = v_ * f.v_;
  res.err_ = (err_ / v_ + f.err_ / f.v_) * res.v_;
  return res;
}

auto EFloat::operator / (const EFloat& f) const -> EFloat
{
  EFloat res;
  res.v_   = v_ / f.v_;
  res.err_ = (err_ / v_ + f.err_ / f.v_) * res.v_;
  return res;
}

EFloat::operator float  () const { return static_cast<float>(v_);  }
EFloat::operator double () const { return static_cast<double>(v_); }

}  // namespace niepce
