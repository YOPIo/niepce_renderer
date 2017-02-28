#include "point3.h"

namespace niepce
{

class Name
{
 public:
  Name();
  virtual ~Name();
};

template class Point3<int>;
template class Point3<Float>;

}  // namespace niepce
