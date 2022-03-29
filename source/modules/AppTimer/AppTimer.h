#ifndef APPTIMER_H
#define APPTIMER_H

#include "IAppTimer.h"
#include "ISystemTime.h"
#include "Types.h"
#include "List.h"

struct TimerStruct
{
  TimerId id;
  uint32_t count;
};

class AppTimer : public IAppTimer
{
private:
  ISystemTime& m_timer;
  List<TimerStruct> timer_list;
  uint32_t number_of_timers;
public:

  AppTimer(ISystemTime& timer, uint32_t max_timers);

  void Process();
  TimerId CreateTimer(uint32_t count, eTimeUnit unit);
  bool Expired(TimerId id);
  void Reload(TimerId id, uint32_t count, eTimeUnit unit);
  bool Delete(TimerId id);
  uint32_t GetNumberTimers();
};

#endif