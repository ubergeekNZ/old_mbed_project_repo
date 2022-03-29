#ifndef ITHERMOPILE_H_
#define ITHERMOPILE_H_

#include <stdint.h>
#include "Types.h"

class IThermopile {
 public:
  virtual ~IThermopile() {}
  virtual void SetHighFrameRate(bool flag) = 0;
  virtual void SetMovingAverage(bool flag) = 0;
  virtual uint8_t ReadMovingAverage() = 0;
  virtual float ReadThermistor() = 0;
  virtual void ReadPixels(ImageStruct *buffer) = 0;
  virtual float ReadSinglePixel(uint8_t pixelnum) = 0;
  virtual void SetPixelOffset(uint32_t id, float value) = 0;
  virtual float GetPixelOffset(uint32_t id) = 0;
};

#endif  // ITHERMOPILE_H_
