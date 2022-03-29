#ifndef TRACKERCOMMANDHANDLER_H_
#define TRACKERCOMMANDHANDLER_H_

#include <string.h>
#include <stdlib.h>
#include "mbed.h"
#include "ICommandHandler.h"
#include "Queue.h"
#include "Events.h"

// Handles commands to fire a burst of either high or low frequency, or set the burst length
class TrackerCommandHandler : public ICommandHandler
{
    Settings &m_settings;
    IQueue<sEvent>& queue;
    sEvent event;
public:
    TrackerCommandHandler(ICommandHandler &handler, Settings &setting, IQueue<sEvent>& queue) : 
        ICommandHandler(handler), m_settings(setting), queue(queue) 
    {
        event.id = 0;
        event.data = 0;
    }

    virtual void handle_command(char command_string[], char arg_string[])
    {
        if (strcmp(command_string, "setthresh") == 0)
        {
            m_settings.TrackerThreshold(atof(arg_string));
        }
        else if (strcmp(command_string, "getthresh") == 0)
        {
            event.id = EVT_GET_THRESHOLD;
            queue.enqueue(event);
        }
        else
        {
            ICommandHandler::handle_command(command_string, arg_string);
        }

    }
};

#endif // TRACKERCOMMANDHANDLER_H_