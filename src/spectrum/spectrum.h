#ifndef _SPECTRUM_H_
#define _SPECTRUM_H_
/*
// ---------------------------------------------------------------------------
*/
#include "../core/niepce.h"
#include <valarray>
/*
// ---------------------------------------------------------------------------
*/
#define FIXED_LENGTH_SPECTRUM_SAMPLE_BEGIN 360
#define FIXED_LENGTH_SPECTRUM_SAMPLE_END   830
#define FIXED_LENGTH_SPECTRUM_NUM_SAMPLES  470
/*
// ---------------------------------------------------------------------------
*/
namespace niepce
{
/*
// ---------------------------------------------------------------------------
*/
class FixedLengthSpectrum
{
  /* FixedLengthSpectrum constructors */
public:
  FixedLengthSpectrum ();
  FixedLengthSpectrum (const std::valarray <Float>& samples);


  /* FixedLengthSpectrum destructor */
public:
  virtual ~FixedLengthSpectrum () = default;


  /* FixedLengthSpectrum public operators*/
public:
  FixedLengthSpectrum (const FixedLengthSpectrum&  spectrum) = default;
  FixedLengthSpectrum (      FixedLengthSpectrum&& spectrum) = default;

  auto operator = (const FixedLengthSpectrum&  spectrum)
    -> FixedLengthSpectrum& = default;
  auto operator = (      FixedLengthSpectrum&& spectrum)
    -> FixedLengthSpectrum& = default;


  /* FixedLengthSpectrum  public operator */
public:
  auto operator + (const FixedLengthSpectrum& spectrum) const
    -> FixedLengthSpectrum;
  auto operator - (const FixedLengthSpectrum& spectrum) const
    -> FixedLengthSpectrum;
  auto operator * (const FixedLengthSpectrum& spectrum) const
    -> FixedLengthSpectrum;
  auto operator * (Float t) const
    -> FixedLengthSpectrum;


  /* FixedLengthSpectrum public methods */
public:
  auto GetSamples () const -> std::valarray <Float>;


  /* FixedLengthSpectrum protected data */
protected:
  std::valarray <Float> samples_;

}; // class FixedLengthSpectrum
/*
// ---------------------------------------------------------------------------
*/
auto operator << (std::ostream& os, const FixedLengthSpectrum& spectrum)
  -> std::ostream&;
/*
// ---------------------------------------------------------------------------
*/
}  // namespace niepce
/*
// ---------------------------------------------------------------------------
*/
#endif // _SPECTRUM_H_
