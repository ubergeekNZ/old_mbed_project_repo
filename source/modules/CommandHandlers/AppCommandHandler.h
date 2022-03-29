#ifndef APPMODECOMMANDHANDLER_H_
#define APPMODECOMMANDHANDLER_H_

#include <string.h>
#include <stdlib.h>

#include "ICommandHandler.h"
#include "mbed.h"
#include "Events.h"

// Handles commands to fire a burst of either high or low frequency, or set the burst length
class AppCommandHandler : public ICommandHandler
{
    Settings &m_settings;
    IQueue<sEvent>& queue;
    sEvent event;
    uint32_t data;
public:
    AppCommandHandler(ICommandHandler &handler, Settings &setting, IQueue<sEvent>& queue) : 
        ICommandHandler(handler), m_settings(setting), queue(queue) 
    {
        event.id = 0;
        event.data = 0;
    }
    virtual void handle_command(char command_string[], char arg_string[])
    {
        if (strcmp(command_string, "setunitid") == 0)
        {
            m_settings.UnitID(atoi(arg_string));
        }
        else if (strcmp(command_string, "getunitid") == 0)
        {
            event.id = EVT_GET_UNIT_ID;
            queue.enqueue(event);
        }
        else if (strcmp(command_string, "setipaddr") == 0)
        {
            // m_settings.IpAddress(atoi(arg_string));
            
            // brek the string up to char 
        }
        else if (strcmp(command_string, "getipaddr") == 0)
        {
            event.id = EVT_GET_IP_ADDR;
            queue.enqueue(event);
        }
        else if (strcmp(command_string, "setmode") == 0)
        {
            m_settings.ApplicationMode(atoi(arg_string));
        }
        else if (strcmp(command_string, "getmode") == 0)
        {
            event.id = EVT_GET_STATE;
            queue.enqueue(event);
        }
        else
        {
            ICommandHandler::handle_command(command_string, arg_string);
        }        
    }
};

#endif // APPMODECOMMANDHANDLER_H_