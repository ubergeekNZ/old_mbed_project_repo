#ifndef NORMALSTATE_H
#define NORMALSTATE_H
 
#include "AppFSM.h"
#include "IState.h"
#include "IComms.h"
#include "ISettings.h"
#include "ITracker.h"

#define STRING_BUFFER_SIZE		(40)

class AppFSM;

class NormalState : public IState
{
protected:
 AppFSM& m_FSM;
 ITracker& m_tracker;
 IComms& m_comm;
 ISettings& m_settings;
 bool m_allowed;
 // TODO: need to do something about this, can't have buffer for all state, need to be shared.
 char str_buffer[STRING_BUFFER_SIZE];
public:
 NormalState(AppFSM& fsm, ITracker& tracker, IComms& comm, ISettings& settings); 
 void OnEntry();
 void OnHandle(sEvent& evt);
 void Update();
 void OnExit();
 uint32_t GetStateID() ;
};
 
#endif // NORMALSTATE_H