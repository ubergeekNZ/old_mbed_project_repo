#include "BootloaderState.h"
#include "AppFSM.h"
#include <iostream>

using namespace std;

// receive the tracker object

// need sram interface for temporary storage

// once it pass the crc check or completion then
// writes to internal flash

BootloaderState::BootloaderState(AppFSM& fsm, IComms& comm) : 
 m_FSM(fsm),
 m_comm(comm)
{
}
 

// options menu

void BootloaderState::OnEntry()
{
	m_comm.transmit_data("Bootloader mode\n");
}

// enum eEvent
// {
// 	EVT_IDLE = 0,
// 	EVT_GET_CONFIG,
// 	EVT_SET_CONFIG,
// 	EVT_GET_FRAME,
// 	EVT_GET_ERROR_LOGS,
// 	EVT_GET_THERMISTOR,
// 	EVT_GET_UNIT_ID,
// 	EVT_SET_PASSWORD,
// 	EVT_SET_DIAGNOSTICS_LEVEL,
// 	EVT_RESET_COUNTER,
// 	EVT_RESET_ERROR_LOGS,
// 	EVT_SEND_COUNTER,
// };

// enum eConfigEvent
// {
// 	EVT_STATE = 0,
// 	EVT_RATE,
// 	EVT_OFFSET,
// 	EVT_THRESHOLD,
// 	EVT_UNIT_NAME,
// 	EVT_IP_ADDR,
// 	EVT_TIME,
// };


// Ymodem


void BootloaderState::OnHandle(sEvent& evt)
{
	switch (evt.id)
	{
		case EVT_IDLE:
		{
			// show menu
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
		default:
		{
			m_comm.transmit_data("Unknown command\n");
			break;
		}
	}
}

void BootloaderState::Update()
{
	// command parser here
	// 
	
	// this changes from parser to ymodem mode
}
 
void BootloaderState::OnExit()
{
 // cout << "BootloaderState::OnExit()" << endl;
}

uint32_t BootloaderState::GetStateID()
{
  return 0;
}