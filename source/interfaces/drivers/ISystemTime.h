#ifndef ISYSTEMTIME_H
#define ISYSTEMTIME_H

#include <stdint.h>
#include <stdlib.h> 

class ISystemTime {
public:
    virtual ~ISystemTime() {}
    virtual uint32_t get_tick() = 0;
    virtual uint32_t get_tick_us() = 0;
    virtual uint32_t get_tick_ms() = 0;
    virtual void wait(float s) = 0;
    virtual void wait_ms(uint32_t ms) = 0;
    virtual void wait_us(uint32_t us) = 0;
    virtual void reset() = 0;
    virtual uint32_t get_system_clock() = 0;
};
#endif // ISYSTEMTIME_H

/** @}*/
