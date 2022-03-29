#include "NormalState.h"
#include "AppFSM.h"
#include <cstdio>
#include <iostream>

using namespace std;
// receive the tracker object

NormalState::NormalState(AppFSM& fsm, ITracker& tracker, IComms& comm, ISettings& settings) : 
 m_FSM(fsm),
 m_tracker(tracker),
 m_comm(comm),
 m_settings(settings),
 m_allowed(false)
{
	// create a list of commands and getters and setters functions
	
}

void NormalState::OnEntry()
{
	m_comm.transmit_data("Normal mode\n");
}

void NormalState::OnHandle(sEvent& evt)
{	
	// if (m_allowed)
	{
		switch (evt.id)
		{
			case EVT_IDLE:
			{

				break;
			}
			case EVT_STATE:
			{
				uint8_t state = atoi(evt.data);

				// check if it is a valid value
				if (state < STATE_MAX)
				{
					m_FSM.SetState(state);
				}
				else
				{
					m_comm.transmit_data("Wrong mode entered. Streaming paused. Press entered to resume.\n");
				}
				break;
			}
			case EVT_SEND_COUNTER:
			{
	        	sprintf(str_buffer, "Tracker - Up %03lu Down: %03lu\n", 
	        			m_tracker.read_up_counter(), m_tracker.read_down_counter());
				m_comm.transmit_data(str_buffer);
				break;
			}
			default:
			{
				m_comm.transmit_data("Unknown command\n");
				break;
			}
		}	
	}
	// else
	// {
	// 	if (evt.id == EVT_ENTER_CODE)
	// 	{
	// 		// convert to atoi
	// 		uint32_t pwd = atoi(evt.data);

	// 		if (pwd == m_settings.Password())
	// 		{
	// 			m_allowed = true;
	// 		}
	// 		else
	// 		{
	// 			m_comm.transmit_data("Incorrect password\n");
	// 		}
	// 	}
	// }
}

void NormalState::Update()
{
	// process comms
	
	// command parser here
}
 
void NormalState::OnExit()
{
 // cout << "NormalState::OnExit()" << endl;
}

uint32_t NormalState::GetStateID()
{
  return 0;
}