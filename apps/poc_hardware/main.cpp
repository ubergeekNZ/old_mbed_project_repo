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

DigitalOut myled(PD_0);
DigitalOut myled2(PD_1);
DigitalOut myled3(PD_2);
// DigitalOut myled4(LED6);
// 
#define FLASH_TIME          (0.2)

bool swap_colors = false;

int main(void)
{
    // infinite loop
    while (1) {
        myled = 1;
        myled2=1;
        myled3 =1;
        // myled4 =1;
        wait(FLASH_TIME);
        if (swap_colors)
        {
            myled = 0;
            myled2 = 1;
            myled3 = 1;
            swap_colors = false;
        }
        else
        {
            myled = 1;
            myled2 = 1;
            myled3 = 0;
            swap_colors = true;
        }
        // myled4= 0;
        wait(FLASH_TIME);
    }
}
