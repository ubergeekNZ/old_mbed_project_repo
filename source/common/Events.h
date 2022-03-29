#ifndef EVENTS_H
#define EVENTS_H

#include <stdint.h>
#include <string.h>

enum eEvent
{
	EVT_IDLE = 0,
	EVT_STATE,
	EVT_GET_OFFSET,
	EVT_SET_OFFSET,
	EVT_GET_RATE,
	EVT_SET_RATE,
	EVT_GET_THRESHOLD,
	EVT_SET_THRESHOLD,
	EVT_GET_UNIT_NAME,
	EVT_SET_UNIT_NAME,
	EVT_GET_IP_ADDR,
	EVT_SET_IP_ADDR,
	EVT_GET_GATEWAY_ADDR,
	EVT_SET_GATEWAY_ADDR,
	EVT_GET_SUBNET_ADDR,
	EVT_SET_SUBNET_ADDR,
	EVT_GET_TIME,
	EVT_SET_TIME,
	EVT_GET_FRAME,
	EVT_GET_ERROR_LOGS,
	EVT_GET_THERMISTOR,
	EVT_GET_UNIT_ID,
	EVT_ENTER_CODE,
	EVT_SET_CODE,
	EVT_SET_DIAGNOSTICS_LEVEL,
	EVT_RESET_COUNTER,
	EVT_RESET_ERROR_LOGS,
	EVT_SEND_COUNTER
};

struct sEvent
{
	uint32_t id;
	char* data;

	bool operator==(const sEvent &rhs) {
		if (memcmp(this,&rhs,sizeof(*this)))
			return false;
		else return true;
	}
};

#endif