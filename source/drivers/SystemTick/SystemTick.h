#ifndef SystemTick_H_
#define SystemTick_H_

#include "mbed.h"
#include "IListener.h"    
#include "ISystemTick.h"

struct EventStruct
{
  bool enable;
  uint32_t period;
  funcPtr event;
};

struct TimerProperties;

class SystemTick : public ISystemTick
{
private:
  static EventStruct event_list[10];
  static uint32_t count;
  uint32_t number_of_event;
  static void interrupt_callback();

public:
  SystemTick();
  ~SystemTick() {}
  void register_event(funcPtr event, uint32_t period);
};

#endif  // SystemTick_H_
