#ifndef _TRACKEROBJECT_H
#define _TRACKEROBJECT_H

// Remove some unused headers from this file
#include "ITracker.h"
#include "Types.h"
#include "Queue.h"

class TrackerObject {
 private:
  uint32_t start_x;
  uint32_t start_y;
  uint32_t current_x;
  uint32_t current_y;
  bool direction;
  float temperature;
  uint32_t activity_count;
  bool counted;
 public:
  TrackerObject(uint32_t x, uint32_t y, float temp);
  UpdateObject(uint32_t x, uint32_t y, float temp);
};

#endif  // _TRACKEROBJECT_H
