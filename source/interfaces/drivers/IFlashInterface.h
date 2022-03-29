#ifndef IFLASHINTERFACE_H
#define IFLASHINTERFACE_H

#include "IFlashInterface.h"

class IFlashInterface
{
public:
  ~IFlashInterface() {}
  virtual void Write8Bits(uint32_t address, uint8_t value) = 0;
  virtual void Write16Bits(uint32_t address, uint16_t value) = 0;
  virtual void Write32Bits(uint32_t address, uint32_t value) = 0;
  virtual void WriteFloat(uint32_t address, float value) = 0;
  virtual uint8_t Read8Bits(uint32_t address) = 0;
  virtual uint16_t Read16Bits(uint32_t address) = 0;
  virtual uint32_t Read32Bits(uint32_t address) = 0;
  virtual float ReadFloat(uint32_t address) = 0;
};

#endif  // IFLASHINTERFACE_H
