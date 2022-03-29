
#ifndef INC_SYSTMETIME_H
#define INC_SYSTMETIME_H

#include "mbed.h"
#include "ISystemTime.h"

 
/** SytemTime class to read the DWT counter
 * 
 * Uses for fine tick measurements, add fine timing delays
 *
 */

class SystemTime : public ISystemTime {
public:
    /** Create a TimeStamp
     *
     */ 
    SystemTime();
    
    /** Read the current tick
     *
     * @returns the tick count
     */
    uint32_t get_tick();
    
    /** Read the current tick in us
     *
     * @returns the tick count
     */
    uint32_t get_tick_us();

    /** Read the current tick in ms
     *
     * @returns the tick count
     */
    uint32_t get_tick_ms();

    void wait(float s);

    void wait_ms(uint32_t ms);

    void wait_us(uint32_t us);

    void reset();

    uint32_t get_system_clock();
};

#endif
