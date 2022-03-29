#ifndef IAPPTIMER_H_
#define IAPPTIMER_H_

#include "stdint.h"
#include "Types.h"

class IAppTimer {
 public:
	virtual ~IAppTimer() {}
	virtual TimerId CreateTimer(uint32_t count, eTimeUnit unit) = 0;
	virtual bool Expired(TimerId id) = 0;
	virtual void Reload(TimerId id, uint32_t count, eTimeUnit unit) = 0;
	virtual bool Delete(TimerId id) = 0;
};

#endif  // IAPPTIMER_H_
