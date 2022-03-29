#ifndef DIAGNOSTICSSTATE_H
#define DIAGNOSTICSSTATE_H
 
#include "AppFSM.h"
#include "IState.h"
#include "IComms.h"
#include "IThermopile.h"

class AppFSM;

class DiagnosticsState : public IState
{
protected:
 AppFSM& m_FSM;
 IThermopile& m_sensor;
 IComms& m_comm;
public:
 DiagnosticsState(AppFSM& fsm, IThermopile& sensor, IComms& comm); 
 void OnEntry();
 void OnHandle(sEvent& evt);
 void Update();
 void OnExit();
 uint32_t GetStateID() ;
};

#endif