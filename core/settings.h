#ifndef _SETTINGS_H_
#define _SETTINGS_H_

#include "niepce.h"
#include "../geometries/point2.h"

namespace niepce
{

struct Settings
{
  /* Settings constructors */
  Settings ();
  Settings (unsigned int width,
            unsigned int height,
            unsigned int num_thread,
            unsigned int samples);
  virtual ~Settings ();

  Settings (const Settings&  settings) = default;
  Settings (      Settings&& settings) = default;


  /* Settings operators*/
  auto operator = (const Settings&  settings) -> Settings& = default;
  auto operator = (      Settings&& settings) -> Settings& = default;


  /* Settings data */
  unsigned int width;         // Image width
  unsigned int height;        // Image height
  unsigned int threads;       // Number of threads
  unsigned int samples;       // Number of samples
  unsigned int super_samples; // Number of super samples
}; // class Settings


}  // namespace niepce

#endif // _SETTINGS_H_
