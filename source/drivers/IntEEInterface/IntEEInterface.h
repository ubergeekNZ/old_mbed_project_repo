#ifndef INTEEINTERFACE_H
#define INTEEINTERFACE_H

#include "IFlashInterface.h"

class IntEEInterface : public IFlashInterface
{
public:
  IntEEInterface();
  void Write8Bits(uint32_t address, uint8_t value);
  void Write16Bits(uint32_t address, uint16_t value);
  void Write32Bits(uint32_t address, uint32_t value);
  void WriteFloat(uint32_t address, float value);
  uint8_t Read8Bits(uint32_t address);
  uint16_t Read16Bits(uint32_t address);
  uint32_t Read32Bits(uint32_t address);
  float ReadFloat(uint32_t address);
};

#endif  // INTEEINTERFACE_H
