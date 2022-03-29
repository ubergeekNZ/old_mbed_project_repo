#include "AppTimer.h"
#include <cstdlib>
#include "GlobalConsts.h"
#include <iostream>

using namespace std; 

AppTimer::AppTimer(ISystemTime& timer, uint32_t max_timers) :
	m_timer(timer),
	timer_list(max_timers),
	number_of_timers(0)
{

}

void AppTimer::Process()
{
	uint32_t current_ms = m_timer.get_tick_ms();

	if (current_ms > 0)
	{
		// browse through the timer list
	    for (uint32_t index = 0; index < number_of_timers; index++)
	    {
	      TimerStruct current_object = timer_list.peekElement(index);

	      if (current_object.count)
	      {
	      	current_object.count--;
	      }
	      timer_list.replaceElement(index, current_object);    
	    }

	    m_timer.reset();
	}
}

TimerId AppTimer::CreateTimer(uint32_t count, eTimeUnit unit)
{
	TimerStruct new_object;
	new_object.id = -1;
	// check if timer list is full
	if (!timer_list.isFull())
	{
		new_object.id = rand() % 1000;
		new_object.count = count * unit_conversion[unit];
		timer_list.push(new_object);
		number_of_timers++;
	}

	return new_object.id;
}

bool AppTimer::Expired(TimerId id)
{
	bool expired = true;
	// browse through the timer list
    for (uint32_t index = 0; index < number_of_timers; index++)
    {
      TimerStruct current_object = timer_list.peekElement(index);

      if (current_object.id == id)
      {
      	if (current_object.count)
      	{
      		expired = false;
      	}
      	break;
      } 
    }
	return expired;
}

void AppTimer::Reload(TimerId id, uint32_t count, eTimeUnit unit)
{
	// update timer
    for (uint32_t index = 0; index < number_of_timers; index++)
    {
      TimerStruct current_object = timer_list.peekElement(index);

      if (current_object.id == id)
      {
      	current_object.count = count * unit_conversion[unit];
      	timer_list.replaceElement(index, current_object); 
      	break;
      }   
    }
}

bool AppTimer::Delete(TimerId id)
{
	bool deleted = false;
	// browse through the timer list
    for (uint32_t index = 0; index < number_of_timers; index++)
    {
      TimerStruct current_object = timer_list.peekElement(index);

      if (current_object.id == id)
      {
      	number_of_timers--;
      	timer_list.removeFromList(index);
      	deleted = true;
      	break;
      } 
    }
	return deleted;
}

uint32_t AppTimer::GetNumberTimers()
{
	return number_of_timers;
}
