#include "SystemTime.h"


volatile uint32_t *DWT_CYCCNT   = (volatile uint32_t *)0xE0001004; //address of the register
volatile uint32_t *DWT_CONTROL  = (volatile uint32_t *)0xE0001000; //address of the register
volatile uint32_t *SCB_DEMCR        = (volatile uint32_t *)0xE000EDFC; //address of the register


SystemTime::SystemTime() {
    *SCB_DEMCR = *SCB_DEMCR | 0x01000000;
    *DWT_CYCCNT = 0; // reset the counter
    *DWT_CONTROL = *DWT_CONTROL | 1 ; // enable the counter
}


uint32_t SystemTime::get_tick(void)
{
    volatile uint32_t count = *DWT_CYCCNT;
    return count;
}

uint32_t SystemTime::get_tick_us(void)
{
    volatile uint32_t count = *DWT_CYCCNT;
    count = (count * 1e6)/SystemCoreClock;
    return count;
}

void SystemTime::wait(float s) {
    wait_us(s * 1000000.0f);
}

void SystemTime::wait_ms(uint32_t ms) {
    wait_us(ms * 1000);
}

void SystemTime::wait_us(uint32_t us)
{
    uint32_t start = get_tick_us();
    while ((get_tick_us() - start) < (uint32_t)us);
}

uint32_t SystemTime::get_tick_ms(void)
{
    volatile uint32_t count = *DWT_CYCCNT;
    count = (count * 1e3)/SystemCoreClock;
    return count;
}

void SystemTime::reset(void)
{
    *DWT_CYCCNT = 0; // reset the counter
}

uint32_t SystemTime::get_system_clock(void)
{
    return SystemCoreClock;
}
