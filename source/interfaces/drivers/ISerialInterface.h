#ifndef ISERIALINTERFACE_H_
#define ISERIALINTERFACE_H_

#include <string>

class ISerialInterface {
 public:
  virtual bool transmit_data(std::string message) = 0;
  virtual char get_received_data() = 0;
  virtual bool new_data_received() = 0;
};

#endif  // ISERIALINTERFACE_H_
