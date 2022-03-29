#ifndef CONFIGURATIONSTATE_H
#define CONFIGURATIONSTATE_H
 
#include "AppFSM.h"
#include "IState.h"
#include "IComms.h"
#include "ITracker.h"
#include "ISettings.h"

#define STRING_BUFFER_SIZE		(40)

class AppFSM;

class ConfigurationState : public IState
{
protected:
 AppFSM& m_FSM;
 ITracker& m_tracker;
 ISettings& m_settings;
 IComms& m_comm;
 char str_buffer[STRING_BUFFER_SIZE];
public:
 ConfigurationState(AppFSM& fsm, ITracker& tracker, ISettings& settings, IComms& comm); 
 void OnEntry();
 void OnHandle(sEvent& evt);
 void Update();
 void OnExit();
 uint32_t GetStateID() ;
};

#endif