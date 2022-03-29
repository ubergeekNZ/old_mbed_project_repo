#ifndef SENSORSTATE_H
#define SENSORSTATE_H
 
#include "AppFSM.h"
#include "IState.h"
#include "IComms.h"
#include "IThermopile.h"

#define STRING_BUFFER_SIZE		(40)

class AppFSM;

class SensorState : public IState
{
protected:
 AppFSM& m_FSM;
 IThermopile& m_sensor;
 IComms& m_comm;
  char str_buffer[STRING_BUFFER_SIZE];
public:
 SensorState(AppFSM& fsm, IThermopile& sensor, IComms& comm); 
 void OnEntry();
 void OnHandle(sEvent& evt);
 void Update();
 void OnExit();
 uint32_t GetStateID() ;
};
 
#endif // SENSORSTATE_H