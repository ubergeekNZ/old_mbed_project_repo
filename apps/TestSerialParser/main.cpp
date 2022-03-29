#include "mbed.h"
#include "GridEye.h"
#include "SystemTick.h"
#include "SerialInterface.h"
#include "Tracker.h"
#include "Settings.h"
#include "Queue.h"
#include "Events.h"
#include "Common.h"
// #include "NullCommandHandler.h"
// #include "AppCommandHandler.h"
// #include "SensorCommandHandler.h"
// #include "TrackerCommandHandler.h"
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

    serial_port_wrapper.transmit_data("Application started!!\n");

    Queue<sEvent> event_queue(EVENT_QUEUE_SIZE);

    SystemTick sys_timer;

    CommandParser cmd_parser(serial_port_wrapper, event_queue, cmd_args, NUM_OF(cmd_args));
    // NonBlockingTimer track_timer(sys_timer, 100, TIME_MS);

    // SramInterface flash;
    // Settings app_settings(flash);
    // GridEye therm_sensor(PB_7, PB_6);

    // Tracker track_object(track_timer, therm_sensor, app_settings, event_queue);
    
    // // Process serial commands
    // NullCommandHandler null_handler;
    // AppCommandHandler app_handler(null_handler, app_settings, event_queue);
    // SensorCommandHandler sensor_handler(app_handler, app_settings, event_queue);
    // TrackerCommandHandler tracker_handler(sensor_handler, app_settings, event_queue);
    // CommandParser command_parser(tracker_handler, serial_port_wrapper);

    // Controller main_controller(app_settings, track_timer, therm_sensor, track_object, event_queue, serial_port_wrapper);

    // infinite loop
    while (1) {

        // command_parser.ProcessMessages();
        // main_controller.Process();
        cmd_parser.ProcessMessages();

        if (!event_queue.isEmpty())
        {
            sEvent event = event_queue.dequeue();

            cout << "RX event:" << event.id << ":" << event.data << endl;
        }
    }
}
