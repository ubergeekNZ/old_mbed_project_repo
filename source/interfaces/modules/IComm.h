#ifndef ICOMMS_H_
#define ICOMMS_H_

#include <string>
#include "stdint.h"

class IComms {
 public:
	virtual ~IComms() {}
	virtual bool transmit_data(std::string message) = 0;
	virtual uint8_t get_received_data() = 0;
	virtual bool new_data_received() = 0;
};

#endif  // ICOMMS_H_
