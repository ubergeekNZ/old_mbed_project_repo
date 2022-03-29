#ifndef ITRACKER_H_
#define ITRACKER_H_

#include "stdint.h"

class ITracker {
 public:
  virtual ~ITracker() {}
  virtual uint32_t read_up_counter() = 0;
  virtual uint32_t read_down_counter() = 0;
  virtual void SetThreshold(float level) = 0;
  virtual float GetThreshold() = 0;
  virtual void SetFrameRate(uint32_t rate) = 0;
  virtual uint32_t GetFrameRate() = 0;
  virtual void ProcessTracker() = 0;
  virtual void Reset() = 0;
};

#endif  // ITRACKER_H_
