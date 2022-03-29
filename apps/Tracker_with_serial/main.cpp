#include "mbed.h"
#include "Events.h"
#include "Queue.h"
#include "GridEye.h"
#include "SystemTime.h"
#include "SerialInterface.h"
#include "SramInterface.h"
#include "Settings.h"
#include "Tracker.h"
#include "AppFSM.h"
#include "BootloaderState.h"
#include "NormalState.h"
#include "SensorState.h"
#include "ConfigurationState.h"
#include "DiagnosticsState.h"
#include "SramInterface.h"
#include "Settings.h"
#include "States.h"
#include "Common.h"
#include "CommandParser.h"
#include "CommandConfig.h"
#include "Controller.h"

#define EVENT_QUEUE_SIZE    (20)



int main(void)
{   
    Queue<sEvent> event_queue(EVENT_QUEUE_SIZE);
    GridEye therm_sensor(PB_7, PB_6);
    Serial serial_port(PA_2, PA_3);
    SramInterface flash;
    Settings app_settings(flash);
    SerialInterface serial_port_wrapper(serial_port);
    SystemTime sys_timer;
    Tracker track_object(sys_timer, therm_sensor, event_queue);
    CommandParser cmd_parser(serial_port_wrapper, event_queue, cmd_args, NUM_OF(cmd_args));

    AppFSM fsm;
    BootloaderState bootloader_state(fsm, serial_port_wrapper);
    NormalState normal_state(fsm, track_object, serial_port_wrapper, app_settings);
    SensorState sensor_state(fsm, therm_sensor, serial_port_wrapper);
    ConfigurationState config_state(fsm, track_object, app_settings, serial_port_wrapper);
    DiagnosticsState diagnostics_state(fsm, therm_sensor, serial_port_wrapper);

    // Add states to the FSM engine and initialize
    fsm.AddState(normal_state, STATE_NORMAL);
    fsm.AddState(sensor_state, STATE_SENSOR);
    fsm.AddState(config_state, STATE_CONFIGURATION);
    // fsm.AddState(diagnostics_state, STATE_DIAGNOSTICS);
    // fsm.AddState(bootloader_state, STATE_BOOTLOADER);
    fsm.InitState(normal_state);

    serial_port_wrapper.transmit_data("Application started!!\n");

    // infinite loop
    while (1) {

        track_object.ProcessTracker();
        cmd_parser.ProcessMessages();
        fsm.Update();

        if (!event_queue.isEmpty())
        {
            sEvent event = event_queue.dequeue();
            fsm.ScheduleEvent(event);
        }

    }
}
