#include "spectrum.h"

namespace niepce
{

template<int n>
Spectrum<n>::Spectrum(Float v)
{
  for (int i = 0; i < n; ++i) { s_[i] = v; }
}

template<int n>
Spectrum<n>::~Spectrum()
{}

template<int n>
auto Spectrum<n>::operator == (const Spectrum& spectrum) const -> bool
{
  for (int i = 0; i < n; ++i)
  {
    if (s_[i] != spectrum.s_[i]) { return false; }
  }
  return true;
}

template<int n>
auto Spectrum<n>::operator != (const Spectrum& spectrum) const -> bool
{
  return !(*this == spectrum);
}

template<int n>
auto Spectrum<n>::operator [] (unsigned int idx) -> Float&
{
  DCHECK(0 <= idx && idx < n);
  return  s_[idx];
}

template<int n>
auto Spectrum<n>::operator [] (unsigned int idx) const -> Float
{
  DCHECK(0 <= idx && idx < n);
  return s_[idx];
}

template<int n>
auto Spectrum<n>::operator + (const Spectrum& spectrum) const -> Spectrum
{
  DCHECK(!spectrum.HasNan());
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret.s_[i] += spectrum[i];  }
  return ret;
}

template<int n>
auto Spectrum<n>::operator - (const Spectrum& spectrum) const -> Spectrum
{
  DCHEKC(!spectrum.Hasnan());
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret -= spectrum[i]; }
}

template<int n>
auto Spectrum<n>::operator * (const Spectrum& spectrum) const -> Spectrum
{
  DCHEKC(!spectrum.HasNan());
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret *= spectrum[i]; };
  return ret;
}

template<int n>
auto Spectrum<n>::operator / (const Spectrum& spectrum) const -> Spectrum
{
  DCHEKC(!spectrum.HasNan());
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret /= spectrum[i]; };
  return ret;
}

template<int n>
auto Spectrum<n>::operator += (const Spectrum& spectrum) -> Spectrum&
{
  DCHECK(spectrum.HanNan());
  for (int i = 0; i < n; ++i) { s_[i] += spectrum[i]; };
  return *this;
}

template<int n>
auto Spectrum<n>::operator -= (const Spectrum& spectrum) -> Spectrum&
{
  DCHECK(spectrum.HanNan());
  for (int i = 0; i < n; ++i) { s_[i] -= spectrum[i]; };
  return *this;
}

template<int n>
auto Spectrum<n>::operator *= (const Spectrum& spectrum) -> Spectrum&
{
  DCHECK(spectrum.HanNan());
  for (int i = 0; i < n; ++i) { s_[i] *= spectrum[i]; };
  return *this;
}

template<int n>
auto Spectrum<n>::operator /= (const Spectrum& spectrum) -> Spectrum&
{
  DCHECK(spectrum.HanNan());
  for (int i = 0; i < n; ++i) { s_[i] /= spectrum[i]; };
  return *this;
}

template<int n>
auto Spectrum<n>::operator * (Float v) const -> Spectrum
{
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret[i] *= v; };
  DCHEKC(!ret.HasNan());
  return ret;
}

template<int n>
auto Spectrum<n>::operator / (Float v) const -> Spectrum
{
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret[i] /= v; };
  DCHEKC(!ret.HasNan());
  return ret;
}

template<int n>
auto Spectrum<n>::operator *= (Float v) -> Spectrum&
{
  for (int i = 0; i < n; ++i) { s_[i] *= v; }
  DCHECK(!HasNan());
  return *this;
}

template<int n>
auto Spectrum<n>::operator /= (Float v) -> Spectrum&
{
  for (int i = 0; i < n; ++i) { s_[i] /= v; }
  DCHECK(!HasNan());
  return *this;
}

template<int n>
auto Spectrum<n>::operator - () const noexcept -> Spectrum
{
  Spectrum<n> ret = *this;
  for (int i = 0; i < n; ++i) { ret[i] = -s_[i]; }
  return ret;
}

template<int n>
auto Spectrum<n>::ToString() const noexcept -> std::string
{
  std::string str = "[";
  for (int i = 0; i < n; ++i)
  {
    str += std::to_string(s_[i]);
    if (i + 1 < n) { str += ", "; }
  }
  str += "]";
  return str;
}

template<int n>
auto Spectrum<n>::HasNan() const -> bool
{
  for (int i = 0; i < n; ++i)
  {
    if ( std::isnan(s_[i]) ) { return true; }
  }
  return false;
}

template<int n>
auto Spectrum<n>::Clamp(Float low, Float high) const -> Spectrum
{
  Spectrum<n> ret = *this;;
  for (int i = 0; i < n; ++i) { ret[i] = niepce::Clamp(ret[i], low, high); }
  DCHECK(!ret.HasNan());
  return ret;
}

template<int n>
auto Spectrum<n>::MaxValue() const -> Float
{
  Float ret = s_[0];
  for (int i = 0; i < n; ++i) { ret = std::max(ret, s_[i]); }
  return ret;
}

template<int n>
auto Spectrum<n>::IsBlack() const noexcept -> bool
{
  for (int i = 0; i < n; ++i)
  {
    if (s_[i] != 0.f) { return false; }
  }
  return true;
}

template<int n>
auto operator * (Float v, const Spectrum<n>& spectrum)
{
  return spectrum * v;
}

template<int n>
auto operator / (Float v, const Spectrum<n>& spectrum)
{
  return spectrum / v;
}

template<int n>
auto operator << (std::ostream& os, const Spectrum<n>& spectrum) -> std::ostream&
{
  return os << spectrum.ToString();
}

template<int n>
auto Pow(const Spectrum<n>& s, Float e) -> Spectrum<n>
{
  Spectrum<n> ret(0.f);
  for (int i = 0; i < n; ++i) { ret[i] = std::pow(s[i], e); }
  DCHECK(!ret.HasNan());
  return ret;
}

template<int n>
auto Exp(const Spectrum<n>& s) -> Spectrum<n>
{
  Spectrum<n> ret(0.f);
  for (int i = 0; i < n; ++i) { ret[i] = std::exp(s[i]); }
  DCHECK(!ret.HasNan());
  return ret;
}

template<int n>
auto Sqrt(const Spectrum<n>& s) -> Spectrum<n>
{
  Spectrum<n> ret(0.f);
  for (int i = 0; i < n; ++i) { ret[i] = std::sqrt(s[i]); }
  DCHECK(!s.HasNan());
  return ret;
}


} // namespace niepce
