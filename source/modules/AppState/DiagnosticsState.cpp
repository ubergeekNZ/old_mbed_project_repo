#include "DiagnosticsState.h"
#include "AppFSM.h"

// receive the grid eye object
// 

// this handles only the sensors


DiagnosticsState::DiagnosticsState(AppFSM& fsm, IThermopile& sensor, IComms& comm) : 
 m_FSM(fsm),
 m_sensor(sensor),
 m_comm(comm)
{
}

// options menu

 
void DiagnosticsState::OnEntry()
{
 	m_comm.transmit_data("Diagnostics mode\n");
}

// enum eEvent
// {
// 	EVT_IDLE = 0,
// 	EVT_GET_CONFIG,
// 	EVT_SET_CONFIG,
// 	EVT_GET_ERROR_LOGS,
// 	EVT_GET_UNIT_ID,
// 	EVT_SET_PASSWORD,
// 	EVT_SET_DIAGNOSTICsS_LEVEL,
// 	EVT_RESET_COUNTER,
// 	EVT_RESET_ERROR_LOGS,
// 	EVT_SEND_COUNTER,
// };

// enum eConfigEvent
// {
// 	EVT_STATE = 0,
// 	EVT_RATE,
// 	EVT_THRESHOLD,
// 	EVT_UNIT_NAME,
// 	EVT_IP_ADDR,
// 	EVT_TIME,
// };
	
void DiagnosticsState::OnHandle(sEvent& evt)
{
  	switch (evt.id)
	{
		case EVT_IDLE:
		{
			// pause and print
			m_comm.transmit_data("Streaming paused. Press entered to resume.\n");
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
		case EVT_GET_THERMISTOR:
		{
			// sprintf(str_buffer, "%lu, %.2f\n", i, frame.pixel[i]);
			break;
		}
		case EVT_GET_FRAME:
		{
			break;
		}
		case EVT_GET_OFFSET:
		{
			break;
		}
		case EVT_SET_OFFSET:
		{
			break;
		}
		default:
		{
			m_comm.transmit_data("Unknown command\n");
			break;
		}
	}
}

void DiagnosticsState::Update()
{
  // Poll rate
  // sprintf(str_buffer, "%lu, %.2f\n", i, frame.pixel[i]);
  
  // command parser here
}
 
void DiagnosticsState::OnExit()
{
 // cout << "DiagnosticsState::OnExit()" << endl;
}

uint32_t DiagnosticsState::GetStateID()
{
  return 2;
}

// possible sensor mode