#ifndef ILISTENER_H_
#define ILISTENER_H_

class IListener {
 public:
  virtual ~IListener() {}
  virtual void notify() = 0;
};

#endif  // ILISTENER_H_
