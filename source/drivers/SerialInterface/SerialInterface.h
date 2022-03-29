#ifndef SERIALINTERFACE_H_
#define SERIALINTERFACE_H_

#include <string>
#include "Queue.h"
#include "IComms.h"
#include "mbed.h"

#define COM_RX_QUEUE_SIZE	(128)

class SerialInterface : public IComms {
 private:
  static Queue <uint8_t> *rxFifo;
  static void interrupt_callback(void);
 public:
  SerialInterface(Serial& com);
  bool transmit_data(std::string message);
  uint8_t get_received_data();
  bool new_data_received();
};

#endif  // SERIALINTERFACE_H_
