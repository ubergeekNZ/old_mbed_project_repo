/* mbed Microcontroller Library
 * Copyright (c) 2006-2013 ARM Limited
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#include "mbed.h"
#include "SystemTime.h"
#include "SerialInterface.h"
#include "AppTimer.h"


DigitalOut myled(LED1);
DigitalOut myled2(LED2);
DigitalOut myled3(LED5);
DigitalOut myled4(LED6);

Serial debug(PA_2, PA_3);
SystemTime timer;

bool toggle[4];


int main(void)
{
    wait_ms(500);

    AppTimer app_timer(timer, 10);
    debug.baud(115200);
    debug.printf("Tracker software running\n");

    TimerId timer_id[4];
    uint32_t time_count[4] = {100, 2000, 3000, 4000};

    for (int i =0; i < 4; i++)
    {
        timer_id[i] = app_timer.CreateTimer(time_count[i], TIME_MS);
    }

    // infinite loop
    while (1) {
        
        if (app_timer.Expired(timer_id[0]))
        {
            if (toggle[0])
            {
                myled = 1;
                toggle[0] = false;
            }
            else
            {
                myled = 0;   
                toggle[0] = true;            
            }
            app_timer.Reload(timer_id[0], time_count[0], TIME_MS);
        }

        if (app_timer.Expired(timer_id[1]))
        {
            if (toggle[1])
            {
                myled2= 1;
                toggle[1] = false;
            }
            else
            {
                myled2= 0;  
                toggle[1] = true;            
            }
            app_timer.Reload(timer_id[1], time_count[1], TIME_MS);
        }

        if (app_timer.Expired(timer_id[2]))
        {
            if (toggle[2])
            {
                myled3 = 1;
                toggle[2] = false;
            }
            else
            {
                myled3 = 0;  
                toggle[2] = true;            
            }
            app_timer.Reload(timer_id[2], time_count[2], TIME_MS);
        }

        if (app_timer.Expired(timer_id[3]))
        {
            if (toggle[3])
            {
                myled4 = 1;
                toggle[3] = false;
            }
            else
            {
                myled4 = 0;    
                toggle[3] = true;            
            }
            app_timer.Reload(timer_id[3], time_count[3], TIME_MS);
        }

        app_timer.Process();
    }
}
