#include "SystemTick.h"
#include <cstdlib>

EventStruct SystemTick::event_list[10];
uint32_t SystemTick::count;


SystemTick::SystemTick()
{
  // Set the systick for 1ms interrupts.
  SysTick_Config(SystemCoreClock / 1000);

  /* Enable TIMER0 interrupt vector in NVIC */
  NVIC_DisableIRQ(SysTick_IRQn);
  NVIC_SetVector(SysTick_IRQn, (uint32_t)&SystemTick::interrupt_callback);
  NVIC_EnableIRQ(SysTick_IRQn);

  // //set systick interrupt priority
  // //4 bits for preemp priority 0 bit for sub priority
  // NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);

  // //i want to make sure systick has highest priority amount all other interrupts
  // NVIC_SetPriority(SysTick_IRQn, 4);

  number_of_event = 0;
  count = 0;
}

void SystemTick::register_event(funcPtr event, uint32_t period)
{
  event_list[0].enable = true;
  event_list[0].event = event;
  event_list[0].period = period;
}

void SystemTick::interrupt_callback()
{
  count++;
  if (event_list[0].enable)
  {
    if (count >= event_list[0].period)
    {
      event_list[0].event();
      count = 0;
    }
  }
}
