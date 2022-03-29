#ifndef CONTROLLER_H
#define CONTROLLER_H

#include "stdint.h"
#include "ProductConfig.h"
#include "States.h"
#include "Settings.h"
#include "NonBlockingTimer.h"
#include "IController.h"
#include "IThermopile.h"
#include "ITracker.h"
#include "IQueue.h"
#include "IComms.h"
#include "Events.h"
#include "mbed.h"


class Controller : public IController
{
private:
  
  Settings& settings;
  NonBlockingTimer& timer; 
  IThermopile& sensor; 
  ITracker& tracker;
  IQueue<sEvent>& queue;  
  IComms& comms;
  eState state; 
  char buffer[20];
  DigitalOut myled;
  bool toggle;
  ImageStruct frame;
  
  void ProcessEvents();

public:

  Controller(Settings& settings, 
              NonBlockingTimer& timer, 
              IThermopile& sensor, 
              ITracker& tracker,
              IQueue<sEvent>& queue,
              IComms& comms);

  void Process();


};

#endif