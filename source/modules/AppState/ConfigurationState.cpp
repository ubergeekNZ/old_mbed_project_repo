#include "ConfigurationState.h"
#include "AppFSM.h"
#include "stm32uid.h"
#include "NetworkUtils.h"
#include <cstdio>
#include <iostream>

using namespace std;
// receive the grid eye object
// 

// this handles only the sensors


ConfigurationState::ConfigurationState(AppFSM& fsm, ITracker& tracker, ISettings& settings, IComms& comm) : 
 m_FSM(fsm),
 m_tracker(tracker),
 m_settings(settings),
 m_comm(comm)
{
}

// options menu

 
void ConfigurationState::OnEntry()
{
 	m_comm.transmit_data("Configuration mode\n");
}

void ConfigurationState::OnHandle(sEvent& evt)
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
		// case EVT_GET_ERROR_LOGS:
		// {

		// 	break;
		// }
		case EVT_GET_UNIT_ID:
		{
			uint32_t idPart1 = STM32_UUID[0];
		    uint32_t idPart2 = STM32_UUID[1];
		    uint32_t idPart3 = STM32_UUID[2];

		    sprintf(str_buffer, "ID:%lu%lu%lu\n", idPart1, idPart2, idPart3);
		    m_comm.transmit_data(str_buffer);
			break;
		}
		// case EVT_SET_CODE:
		// {
		// 	// convert to atoi - need to ask the user for entering again before commiting
		// 	break;
		// }
		// case EVT_GET_UNIT_NAME:
		// {

		// 	break;
		// }
		// case EVT_SET_UNIT_NAME:
		// {

		// 	break;
		// }
		case EVT_GET_IP_ADDR:
		{
			uint32_t ip_addr = m_settings.IpAddress();

			// cout << "get ip address: " << ip_addr << endl;
			// m_comm.transmit_data("Get IP address:");
			m_comm.transmit_data(getIPV4string(ip_addr));
			break;
		}
		case EVT_SET_IP_ADDR:
		{
			uint32_t ip_addr = parseIPV4string(evt.data);
			m_settings.IpAddress(ip_addr);
			m_comm.transmit_data("OK");
			break;
		}
		case EVT_GET_GATEWAY_ADDR:
		{
			uint32_t ip_addr = m_settings.GatewayAddress();
			m_comm.transmit_data(getIPV4string(ip_addr));
			break;
		}
		case EVT_SET_GATEWAY_ADDR:
		{
			uint32_t ip_addr = parseIPV4string(evt.data);
			m_settings.GatewayAddress(ip_addr);
			m_comm.transmit_data("OK");			
			break;
		}
		case EVT_GET_SUBNET_ADDR:
		{
			uint32_t ip_addr = m_settings.SubnetAddress();
			m_comm.transmit_data(getIPV4string(ip_addr));
			break;
		}
		case EVT_SET_SUBNET_ADDR:
		{
			uint32_t ip_addr = parseIPV4string(evt.data);
			m_settings.SubnetAddress(ip_addr);
			m_comm.transmit_data("OK");			
			break;
		}
		// case EVT_GET_TIME:
		// {

		// 	break;
		// }
		// case EVT_SET_TIME:
		// {

		// 	break;
		// }
		case EVT_GET_RATE:
		{
			sprintf(str_buffer, "Framerate: %lu\n", 
				m_tracker.GetFrameRate());
			m_comm.transmit_data(str_buffer);
			break;
		}
		case EVT_SET_RATE:
		{
			uint32_t rate = atoi(evt.data);

			if (rate <= 10 && rate > 0)
			{
				m_tracker.SetFrameRate(rate);
				m_comm.transmit_data("OK");
			}
			else
			{
				m_comm.transmit_data("Framerate is out of bound (1 to 10)\n");
			}
			break;
		}
		case EVT_GET_THRESHOLD:
		{
			sprintf(str_buffer, "Framerate: %f\n", 
				m_tracker.GetThreshold());
			m_comm.transmit_data(str_buffer);
			break;
		}
		case EVT_SET_THRESHOLD:
		{
			float level = atof(evt.data);

			if (level > 0)
			{
				m_tracker.SetThreshold(level);
				m_comm.transmit_data("OK");
			}
			else
			{
				m_comm.transmit_data("Threshold is 0\n");
			}
			break;
		}
		case EVT_RESET_COUNTER:
		{
			m_tracker.Reset();
			m_comm.transmit_data("OK");
			break;
		}
		// case EVT_RESET_ERROR_LOGS:
		// {
		// 	// TODO
		// 	break;
		// }
		default:
		{
			m_comm.transmit_data("Unknown command\n");
			break;
		}
	}
}

void ConfigurationState::Update()
{
  // Poll rate
  // sprintf(str_buffer, "%lu, %.2f\n", i, frame.pixel[i]);
  
  // command parser here
}
 
void ConfigurationState::OnExit()
{
 // cout << "ConfigurationState::OnExit()" << endl;
}

uint32_t ConfigurationState::GetStateID()
{
  return 2;
}

// possible sensor mode