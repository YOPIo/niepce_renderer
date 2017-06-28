#include "settings.h"

namespace niepce
{

Settings::Settings ()
{}

Settings::Settings (unsigned int w,
                    unsigned int h,
                    unsigned int t,
                    unsigned int s) :
    width   (w),
    height  (h),
    threads (t),
    samples (s)
{}

Settings::~Settings ()
{}

}  // namespace niepce
