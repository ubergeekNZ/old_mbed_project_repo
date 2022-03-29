#ifndef MOCKFLASH_H_
#define MOCKFLASH_H_

#include "gmock/gmock.h"
#include "IFlashInterface.h"

class MockFlash : public IFlashInterface
{
public:
	MOCK_METHOD2(Write8Bits, void(uint32_t address, uint8_t value));
	MOCK_METHOD2(Write16Bits, void(uint32_t address, uint16_t value));
	MOCK_METHOD2(Write32Bits, void(uint32_t address, uint32_t value));
	MOCK_METHOD2(WriteFloat, void(uint32_t address, float value));
	MOCK_METHOD1(Read8Bits, uint8_t(uint32_t address));
	MOCK_METHOD1(Read16Bits, uint16_t(uint32_t address));
	MOCK_METHOD1(Read32Bits, uint32_t(uint32_t address));
	MOCK_METHOD1(ReadFloat, float(uint32_t address));
};

#endif // MOCKFLASH_H_