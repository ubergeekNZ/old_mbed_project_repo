#ifndef COMMANDCONFIG_H
#define COMMANDCONFIG_H

#include "Types.h"


// List of commands in a table
const CommandArgs cmd_args [] = 
{ 
    { EVT_IDLE , ""},
    { EVT_STATE, "setstate" },
    { EVT_GET_OFFSET, "getoffset" },
    { EVT_SET_OFFSET, "setoffset" },
    { EVT_GET_RATE, "getrate" },
    { EVT_SET_RATE, "setrate" },
    { EVT_GET_THRESHOLD, "getthreshold" },
    { EVT_SET_THRESHOLD, "setthreshold" },
    { EVT_GET_UNIT_NAME, "getunitname" },
    { EVT_SET_UNIT_NAME, "setunitname" },
    { EVT_GET_IP_ADDR, "getipaddress" },
    { EVT_SET_IP_ADDR, "setipaddress" },
    { EVT_GET_TIME, "gettime" },
    { EVT_SET_TIME, "settime" },
    { EVT_GET_FRAME, "getframe" },
    { EVT_GET_ERROR_LOGS, "geterrorlogs" },
    { EVT_GET_THERMISTOR, "getthermistor" },
    { EVT_GET_UNIT_ID, "getunitid" },
    { EVT_ENTER_CODE, "entercode" },
    { EVT_SET_CODE, "setcode" },
    { EVT_SET_DIAGNOSTICS_LEVEL, "setdiagnostics" },
    { EVT_RESET_COUNTER, "resetcounter" },
    { EVT_RESET_ERROR_LOGS, "resetlogs" },
    { EVT_SEND_COUNTER, "getcounter" }
};

#endif