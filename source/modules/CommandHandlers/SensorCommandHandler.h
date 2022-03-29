#ifndef SENSORCOMMANDHANDLER_H_
#define SENSORCOMMANDHANDLER_H_

#include <string.h>
#include <stdlib.h>
#include "mbed.h"
#include "ICommandHandler.h"
#include "Events.h"

// Handles commands to fire a burst of either high or low frequency, or set the burst length
// Need to pass in event queue
class SensorCommandHandler : public ICommandHandler
{
    Settings &m_settings;
    IThermopile& sensor;
    IQueue<sEvent>& queue;
    sEvent event;
public:
    SensorCommandHandler(ICommandHandler &handler, Settings &settings, IQueue<sEvent>& queue) : 
        ICommandHandler(handler), m_settings(settings), sensor(sensor), queue(queue) 
    {
        event.id = 0;
        event.data = 0;
    }
    virtual void handle_command(char command_string[], char arg_string[])
    {
        if (strcmp(command_string, "setrate") == 0)
        {
            m_settings.SensorFrameRate(1000/atoi(arg_string));
        }
        else if (strcmp(command_string, "getrate") == 0)
        {
            event.id = EVT_GET_RATE;
            queue.enqueue(event);
        }
        else if (strcmp(command_string, "setoffset") == 0)
        {
            char *set_string = strtok(arg_string, ",");
            uint32_t pixel = atoi(set_string);
            set_string = strtok(NULL, "\0");
            float offset = atof(set_string);

            m_settings.SetSensorOffset(pixel, offset);
        }
        else if (strcmp(command_string, "getoffset") == 0)
        {
            event.id = EVT_GET_OFFSET;
            queue.enqueue(event);
        }
        else if (strcmp(command_string, "getframe") == 0)
        {
            event.id = EVT_GET_FRAME;
            queue.enqueue(event);
        }
        else if (strcmp(command_string, "gettemp") == 0)
        {
            event.id = EVT_GET_THERMISTOR;
            queue.enqueue(event);
        } 
        else
        {
            ICommandHandler::handle_command(command_string, arg_string);
        }        
    }
};

#endif // SENSORCOMMANDHANDLER_H_