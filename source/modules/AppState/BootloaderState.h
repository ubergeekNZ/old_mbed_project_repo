#ifndef BOOTLOADERSTATE_H
#define BOOTLOADERSTATE_H
 
#include "AppFSM.h"
#include "IState.h"
#include "IComms.h"
#include "ISettings.h"

class AppFSM;

class BootloaderState : public IState
{
protected:
 AppFSM& m_FSM;
 IComms& m_comm;
public:
 BootloaderState(AppFSM& fsm, IComms& comm); 
 void OnEntry();
 void OnHandle(sEvent& evt);
 void Update();
 void OnExit();
 uint32_t GetStateID() ;
};
 
#endif // BOOTLOADERSTATE_H