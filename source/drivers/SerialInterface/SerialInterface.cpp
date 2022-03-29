#include <string>
#include "SerialInterface.h"

// change serial interface to use iSerial from mbed

Queue <uint8_t> *SerialInterface::rxFifo;
static Serial* com_port;

SerialInterface::SerialInterface(Serial& com)
{
  rxFifo = new Queue<uint8_t>(COM_RX_QUEUE_SIZE);
  com_port = &com;
  com_port->baud(115200);
  com_port->attach(&interrupt_callback, Serial::RxIrq);
  transmit_data("Serial interface setup\n");
}

bool SerialInterface::transmit_data(std::string message)
{
  if (com_port->readable()) {
    return false;
  } 

  for (uint32_t count = 0; count < message.length(); count++)
  {
    com_port->putc(message[count]);
  }
  return true;
}

uint8_t SerialInterface::get_received_data()
{
  return rxFifo->dequeue();
}

bool SerialInterface::new_data_received()
{
  return !rxFifo->isEmpty();
}

void SerialInterface::interrupt_callback(void)
{
  while (com_port->readable()) {
      uint8_t data = com_port->getc();
      rxFifo->enqueue(data);
  }
}
