#ifndef IMESSAGELISTENER_H_
#define IMESSAGELISTENER_H_

class IMessageListener {
 public:
  virtual ~IMessageListener() {}
  virtual void notify(uint32_t data) = 0;
};

#endif  // IMESSAGELISTENER_H_
