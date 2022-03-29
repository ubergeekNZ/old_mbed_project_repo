#include "stm32f4xx.h"
#include "stm32f4xx_hal_flash.h"
#include "IntEEInterface.h"


// HAL_StatusTypeDef HAL_FLASH_Program(uint32_t TypeProgram, uint32_t Address, uint64_t Data)
// 
IntEEInterface::IntEEInterface() 
{

}

void IntEEInterface::Write16Bits(uint32_t address, uint16_t value)
{

}

void IntEEInterface::Write32Bits(uint32_t address, uint32_t value)
{

}

void IntEEInterface::WriteFloat(uint32_t address, float value)
{

}

uint8_t IntEEInterface::Read8Bits(uint32_t address)
{
  return 0;
}

uint16_t IntEEInterface::Read16Bits(uint32_t address)
{
  return 0;
}

uint32_t IntEEInterface::Read32Bits(uint32_t address)
{
  return 0;
}

float IntEEInterface::ReadFloat(uint32_t address)
{
  return 0;
}
