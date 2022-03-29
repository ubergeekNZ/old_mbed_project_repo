#include "mbed.h"
#include "Events.h"
#include "Queue.h"
#include "GridEye.h"
#include "SystemTime.h"
#include "SerialInterface.h"
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
#include "Controller.h"

#define EVENT_QUEUE_SIZE    (20)

Queue<sEvent> event_queue(EVENT_QUEUE_SIZE);
DigitalOut myled(LED1);
GridEye therm_sensor(PB_7, PB_6);
Serial serial_port(PA_2, PA_3);
SerialInterface serial_port_wrapper(serial_port);
SystemTime sys_timer;
Tracker track_object(sys_timer, therm_sensor, event_queue);


int main(void)
{   
    serial_port_wrapper.transmit_data("Application started!!\n");

    

    // setup eeprom and sram - sram is use for temp storage
    // SramInterface flash;
    // Settings app_settings(flash);

    // Setup tracker
    

    // need to create a bootloader object - this takes in ymodem and write to flash
    // need to ensure separation

    // need to create a network object which gets pass to all the state
    // each state monitor for connection
    // if connection then network terminal starts else just serial

    

    // setup the command parser
    

    // Setup the fsm
    // AppFSM fsm;
    // BootloaderState bootloader_state(fsm, serial_port_wrapper);
    // NormalState normal_state(fsm, track_object, serial_port_wrapper);
    // SensorState sensor_state(fsm, therm_sensor, serial_port_wrapper);
    // ConfigurationState config_state(fsm, therm_sensor, serial_port_wrapper);
    // DiagnosticsState diagnostics_state(fsm, therm_sensor, serial_port_wrapper);

    // // Add states to the FSM engine and initialize
    // fsm.AddState(normal_state, STATE_NORMAL);
    // fsm.AddState(sensor_state, STATE_SENSOR);
    // fsm.AddState(bootloader_state, STATE_BOOTLOADER);
    // fsm.AddState(config_state, STATE_CONFIGURATION);
    // fsm.AddState(diagnostics_state, STATE_DIAGNOSTICS);
    // fsm.InitState(config_state);

    // // Setup application controller
    // Controller app_controller(fsm, app_settings, event_queue);

    // delay for sensor to power up
    // wait_ms(500);

    // infinite loop
    while (1) {
        // track_object.ProcessTracker();
        // app_controller.Process();

        track_object.ProcessTracker();

        if (!event_queue.isEmpty())
        {
            sEvent event = event_queue.dequeue();

            if (event.id == EVT_SEND_COUNTER)
            {
                serial_port.printf("Tracker - Up: %03d Down: %03d\n", //
                track_object.read_up_counter(), track_object.read_down_counter());
            }
        }

    }
}
