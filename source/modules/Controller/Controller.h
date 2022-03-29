#ifndef CONTROLLER_H
#define CONTROLLER_H

// #include "stdint.h"
#include "ProductConfig.h"
#include "ISettings.h"
#include "IController.h"
#include "IQueue.h"
#include "IFSM.h"
#include "Events.h"


class Controller : public IController
{
private:
  IFSM& m_fsm;
  ISettings& m_settings;
  IQueue<sEvent>& m_queue;  
  void ProcessEvents();

public:

  Controller(IFSM& fsm,
             ISettings& settings, 
             IQueue<sEvent>& queue);

  void Process();


};

#endif