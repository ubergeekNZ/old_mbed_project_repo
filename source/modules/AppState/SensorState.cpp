#include "SensorState.h"
#include "AppFSM.h"
#include <cstdio>
#include <iostream>

using namespace std;
// receive the grid eye object
// 

// this handles only the sensors


SensorState::SensorState(AppFSM& fsm, IThermopile& sensor, IComms& comm) : 
 m_FSM(fsm),
 m_sensor(sensor),
 m_comm(comm)
{
}

 
void SensorState::OnEntry()
{
 	m_comm.transmit_data("Sensor mode\n");
}


void SensorState::OnHandle(sEvent& evt)
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
			float temp = m_sensor.ReadThermistor();
			int intpart = (int)temp;
    		int decimalpart = (int)((temp-(float)intpart)*100.0f);
			sprintf(str_buffer, "%d.%02d\n", intpart,decimalpart);
			m_comm.transmit_data(str_buffer);
			break;
		}
		case EVT_GET_FRAME:
		{
			memset(str_buffer, 0, sizeof(str_buffer));
			ImageStruct frame;
	        for(int pixel = 0; pixel < 64; pixel++)
	        {
	            frame.pixel[pixel] = m_sensor.ReadSinglePixel(pixel);
	        }
	        m_comm.transmit_data("{");
	        for(int pixel = 0; pixel < 64; pixel++)
	        {
	        	int intpart = (int)frame.pixel[pixel];
    			int decimalpart = (int)((frame.pixel[pixel]-(float)intpart)*100.0f);
	        	sprintf(str_buffer, "%d.%02d,", intpart,decimalpart);
	        	m_comm.transmit_data(str_buffer);
	        }
			m_comm.transmit_data("}\n");
			break;
		}
		case EVT_GET_OFFSET:
		{
			uint8_t index = atoi(evt.data);
			if (index < 64)
			{
				float temp = m_sensor.GetPixelOffset(index);
				int intpart = (int)temp;
	    		int decimalpart = (int)((temp-(float)intpart)*100.0f);
				sprintf(str_buffer, "%d.%02d\n", intpart,decimalpart);
				m_comm.transmit_data(str_buffer);
			}
			else
			{
				m_comm.transmit_data("Out of bound value\n");
			}
			break;
		}
		case EVT_SET_OFFSET:
		{
			char *pixelnum = strtok(evt.data, ",");
            char *pixelvalue = strtok(NULL, ",");
            uint8_t index = atoi(pixelnum);
			float value = atof(pixelvalue);
			if (value > 0.0f && value < 5.0f && index < 64)
			{
				m_sensor.SetPixelOffset(index, value);
				m_comm.transmit_data("Ok\n");
			}
			else
			{
				m_comm.transmit_data("Out of bound value\n");
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

void SensorState::Update()
{
  // Poll rate
  // sprintf(str_buffer, "%lu, %.2f\n", i, frame.pixel[i]);
  
  // command parser here
}
 
void SensorState::OnExit()
{
 // cout << "SensorState::OnExit()" << endl;
}

uint32_t SensorState::GetStateID()
{
  return 2;
}

// possible sensor mode