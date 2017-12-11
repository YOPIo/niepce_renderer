#include "spectrum.h"
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
FixedLengthSpectrum::FixedLengthSpectrum () :
  samples_ (std::valarray <Float> (FIXED_LENGTH_SPECTRUM_NUM_SAMPLES))
{}
/*
// ---------------------------------------------------------------------------
*/
auto FixedLengthSpectrum::operator + (const FixedLengthSpectrum& spectrum)
  const -> FixedLengthSpectrum
{
  return FixedLengthSpectrum (samples_ + spectrum.samples_);
}
/*
// ---------------------------------------------------------------------------
*/
auto FixedLengthSpectrum::operator - (const FixedLengthSpectrum& spectrum)
  const -> FixedLengthSpectrum
{
  return FixedLengthSpectrum (samples_ - spectrum.samples_);
}
/*
// ---------------------------------------------------------------------------
*/
auto FixedLengthSpectrum::operator * (const FixedLengthSpectrum& spectrum)
  const -> FixedLengthSpectrum
{
  return FixedLengthSpectrum (samples_ * spectrum.samples_);
}
/*
// ---------------------------------------------------------------------------
*/
auto FixedLengthSpectrum::operator * (Float t) const -> FixedLengthSpectrum
{
  return FixedLengthSpectrum (samples_ * t);
}
/*
// ---------------------------------------------------------------------------
*/
auto operator << (std::ostream& os, const FixedLengthSpectrum& spectrum)
  -> std::ostream&
{
  os << "Wavelength : value\n";
  const std::valarray <Float>& samples (spectrum.GetSamples ());
  for (int i = 0; i < samples.size (); ++i)
  {
    os << "["   << FIXED_LENGTH_SPECTRUM_SAMPLE_BEGIN + i
       << " : " << samples[i]
       << "]\n";
  }

  return os;
}
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
