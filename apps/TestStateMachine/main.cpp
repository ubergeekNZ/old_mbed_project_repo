#include "mbed.h"
#include "GridEye.h"
#include "SystemTime.h"
#include "SerialInterface.h"
#include "Tracker.h"
#include "Settings.h"
#include "Queue.h"
#include "Events.h"
#include "Common.h"
#include "AppFSM.h"
#include "BootloaderState.h"
#include "NormalState.h"
#include "SensorState.h"
#include "ConfigurationState.h"
#include "DiagnosticsState.h"
#include "Controller.h"
#include "CommandParser.h"
#include "SramInterface.h"
#include "CommandConfig.h"
#include <iostream>

using namespace std;

#define EVENT_QUEUE_SIZE    (20)


int main(void)
{
    Serial serial_port(PA_2, PA_3);
    SerialInterface serial_port_wrapper(serial_port);
    GridEye therm_sensor(PB_7, PB_6);
    
    serial_port_wrapper.transmit_data("Application started!!\n");

    Queue<sEvent> event_queue(EVENT_QUEUE_SIZE);

    SystemTime sys_timer;
    Tracker track_object(sys_timer, therm_sensor, event_queue);

    CommandParser cmd_parser(serial_port_wrapper, event_queue, cmd_args, NUM_OF(cmd_args));
    
    // Setup the fsm
    AppFSM fsm;
    BootloaderState bootloader_state(fsm, serial_port_wrapper);
    NormalState normal_state(fsm, track_object, serial_port_wrapper);
    SensorState sensor_state(fsm, therm_sensor, serial_port_wrapper);
    ConfigurationState config_state(fsm, therm_sensor, serial_port_wrapper);
    DiagnosticsState diagnostics_state(fsm, therm_sensor, serial_port_wrapper);

    // Add states to the FSM engine and initialize
    fsm.AddState(normal_state, STATE_NORMAL);
    fsm.AddState(sensor_state, STATE_SENSOR);
    fsm.AddState(bootloader_state, STATE_BOOTLOADER);
    fsm.AddState(config_state, STATE_CONFIGURATION);
    fsm.AddState(diagnostics_state, STATE_DIAGNOSTICS);
    fsm.InitState(config_state);
    
    // infinite loop
    while (1) {

        // command_parser.ProcessMessages();
        // main_controller.Process();
        cmd_parser.ProcessMessages();
        fsm.Update();

        if (!event_queue.isEmpty())
        {
            sEvent event = event_queue.dequeue();
            fsm.ScheduleEvent(event);
        }
    }
}
