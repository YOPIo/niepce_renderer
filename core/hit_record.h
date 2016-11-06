#ifndef _HIT_RECORD_H_
#define _HIT_RECORD_H_

#include <climits>

#include "../3rdparty/glm/glm.hpp"
#include "ray.h"

namespace niepce
{

struct HitRecord
{
 public:
  HitRecord();
  virtual ~HitRecord();

  HitRecord(const HitRecord& hit_record) = default;
  HitRecord(HitRecord&& hit_record)      = default;
  HitRecord& operator = (const HitRecord& hit_record) = default;
  HitRecord& operator = (HitRecord&& hit_record)      = default;

  float     distance_;
  glm::vec3 position_;
  glm::vec3 normal_;
};



} // namespace niepce

#endif // _HIT_RECORD_H_
