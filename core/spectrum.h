#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_

#include "niepce.h"

namespace niepce
{

static const int kSampledLambdaStart = 400;
static const int kSampledLambdaEnd   = 700;
static const int kSpectralSamples    = 60;

template<int kSpectrumSamples>
class Spectrum
{
 public:
  Spectrum(Float v = 0.f);
  virtual ~Spectrum();

  Spectrum(const Spectrum& spectrum) = default;
  Spectrum(Spectrum&& spectrum)      = default;

  auto operator = (const Spectrum& spectrum) -> Spectrum& = default;
  auto operator = (Spectrum&& spectrum)      -> Spectrum& = default;

  auto operator == (const Spectrum& s) const -> bool;
  auto operator != (const Spectrum& s) const -> bool;

  auto operator [] (unsigned int idx)       -> Float&;
  auto operator [] (unsigned int idx) const -> Float;

  auto operator + (const Spectrum& s) const -> Spectrum;
  auto operator - (const Spectrum& s) const -> Spectrum;
  auto operator * (const Spectrum& s) const -> Spectrum;
  auto operator / (const Spectrum& s) const -> Spectrum;

  auto operator += (const Spectrum& s) -> Spectrum&;
  auto operator -= (const Spectrum& s) -> Spectrum&;
  auto operator *= (const Spectrum& s) -> Spectrum&;
  auto operator /= (const Spectrum& s) -> Spectrum&;

  auto operator * (Float v) const -> Spectrum;
  auto operator / (Float v) const -> Spectrum;
  auto operator *= (Float v) -> Spectrum&;
  auto operator /= (Float v) -> Spectrum&;

  auto operator - () const noexcept -> Spectrum;

  auto ToString() const noexcept -> std::string;
  auto Clamp(Float low = 0, Float high = kInfinity) const -> Spectrum;
  auto HasNan() const -> bool;
  auto MaxValue() const -> Float;
  auto IsBlack() const noexcept -> bool;

  friend auto operator * (Float v, const Spectrum& s) -> Spectrum;
  friend auto operator / (Float v, const Spectrum& s) -> Spectrum;

  friend auto operator << (std::ostream& os, const Spectrum& s) -> std::ostream;

  friend auto Pow(const Spectrum& s, Float e) -> Spectrum;
  friend auto Exp(const Spectrum& s)          -> Spectrum;
  friend auto Sqrt(const Spectrum& s)         -> Spectrum;

 public:
  static const int kSamples = kSpectrumSamples;

 protected:
  std::array<Float, kSpectrumSamples> s_;
}; // class Spectrum

} // namespace niepce

#endif // _SPECTRUM_H_
