#ifndef ISYSTEMTICK_H_
#define ISYSTEMTICK_H_

#include "Types.h"

class ISystemTick
{
public:
  virtual void register_event(funcPtr event, uint32_t period) = 0;
};

#endif  // ISYSTEMTICK_H_
