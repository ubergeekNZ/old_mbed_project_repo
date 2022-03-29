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
#include "GridEye.h"
#include "SystemTick.h"
#include "SerialInterface.h"

DigitalOut myled(LED1);
// DigitalOut myled2(LED2);
// DigitalOut myled3(LED5);
// DigitalOut myled4(LED6);

// I2C i2c(PB_7, PB_6);
Serial debug(PA_2, PA_3);

// const uint8_t I2C_ADDR = 0x68; 
// const char therml_addr = 0x0E;
// const char thermh_addr = 0x0F;
// const char normal_addr = 0x00;


void PrintFloat(float value)
{
    int intpart = (int)value;
    int decimalpart = (int)((value-(float)intpart)*100.0f);
    debug.printf("%d.%02d", intpart,decimalpart);
}

// void ReadThermistor()
// {
//     char temp_read[2];
//     i2c.write(I2C_ADDR << 1, &therml_addr, 1, false);
//     i2c.read(I2C_ADDR << 1, &temp_read[0], 2 );
//     int temperatureTherm = ((temp_read[1] << 8) | temp_read[0]);
//     float celsiusTherm = temperatureTherm*0.0625;
//     debug.printf("Thermistor values ");
//     PrintFloat(celsiusTherm);
// }

// void ReadPixel()
// {
//     float celsius;
//     char pixel_addr = 0x80;
//     char temp_read[2];

//     for(int pixel = 0; pixel < 64; pixel++)
//     {
//         i2c.write(I2C_ADDR << 1, &pixel_addr, 1, false);
//         i2c.read(I2C_ADDR << 1, &temp_read[0], 2 );

//         //Convert temperature
//         int temperature = ((temp_read[1] << 8) | temp_read[0]);
//         if (temperature > 2047){
//           temperature = temperature - 4096;
//         }

//         celsius = temperature * 0.25;

//         debug.printf("Pixel %d = ", pixel);
//         PrintFloat(celsius);

//         pixel_addr = pixel_addr + 2;
//     }
// }

GridEye therm_sensor(PB_7, PB_6);


int main(void)
{
    // i2c.frequency(100000);
    debug.baud(115200);
    debug.printf("Tracker software running\n");
    therm_sensor.SetMovingAverage(true);
    debug.printf("Ave Reg %x\n", therm_sensor.ReadMovingAverage());

    // infinite loop
    while (1) {
        // myled = 1;
        // myled2=1;
        // myled3 =1;
        // myled4 =1;
        // wait(0.2);
        // myled = 0;
        // myled2 = 0;
        // myled3 = 0;
        // myled4= 0;
        // wait(0.2);
        
        wait_ms(100);
        debug.printf("\nT=");
        PrintFloat(therm_sensor.ReadThermistor());
        debug.printf("\n");

        debug.printf("{");
        for(int pixel = 0; pixel < 64; pixel++)
        {
            PrintFloat(therm_sensor.ReadSinglePixel(pixel));
            debug.printf(",");
        }
        debug.printf("}");
        // ReadPixel();
        // ReadThermistor();
        // 

    }
}
