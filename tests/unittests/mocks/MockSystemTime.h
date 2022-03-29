#ifndef MOCKSYSTEMTIME_H_
#define MOCKSYSTEMTIME_H_

#include "gmock/gmock.h"
#include "ISystemTime.h"

class MockSystemTime : public ISystemTime
{
public:
	MOCK_METHOD0(get_tick, uint32_t());
	MOCK_METHOD0(get_tick_us, uint32_t());
	MOCK_METHOD0(get_tick_ms, uint32_t());
	MOCK_METHOD1(wait, void(float s));
	MOCK_METHOD1(wait_ms, void(uint32_t ms));
	MOCK_METHOD1(wait_us, void(uint32_t us));
	MOCK_METHOD0(reset, void());
	MOCK_METHOD0(get_system_clock, uint32_t());
};

#endif // MOCKSYSTEMTIME_H_
