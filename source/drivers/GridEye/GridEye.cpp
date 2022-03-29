#include "GridEye.h"

// TODO - need to perform a block read of the I2C sensor

GridEye::GridEye(PinName sda, PinName scl) :
	i2c(sda, scl),
    threshold(false)
{
    SetMovingAverage(true);
    
    for (int i = 0; i < MAX_PIXEL_INDEX; i++)
    {
        pixel_offset[i] = 0.0f;
    }
}

void GridEye::SetHighFrameRate(bool flag)
{
    char temp[2];
    temp[0] = FRAMERATE_ADDR;
    temp[1] = (char)flag;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
}

void GridEye::SetMovingAverage(bool flag)
{
    char temp[2];
    temp[0] = 0x1F;
    temp[1] = 0x50;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
    temp[0] = 0x1F;
    temp[1] = 0x45;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
    temp[0] = 0x1F;
    temp[1] = 0x57;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
    temp[0] = AVE_ADDR;
    if (flag)
        temp[1] = 0x20;
    else
        temp[1] = 0x00;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
    temp[0] = 0x1F;
    temp[1] = 0x00;
    i2c.write(I2C_ADDR << 1, &temp[0], 2, false);
}

uint8_t GridEye::ReadMovingAverage()
{
    char temp[2];
    char data;
    temp[0] = AVE_ADDR;
    i2c.write(I2C_ADDR << 1, &temp[0], 1, false);
    i2c.read(I2C_ADDR << 1, &data, 1 );
    return data;
}

void GridEye::SetThreshold(bool flag)
{
    threshold = flag;
}

float GridEye::ReadThermistor()
{
	char temp[2];
	temp[0] = THERML_ADDR;
    i2c.write(I2C_ADDR << 1, &temp[0], 1, false);
    i2c.read(I2C_ADDR << 1, &temp[0], 2 );
    int temperatureTherm = ((temp[1] << 8) | temp[0]);
    float celsiusTherm = temperatureTherm*0.0625;

    return celsiusTherm;
}

void GridEye::ReadPixels(ImageStruct *buffer)
{
    // char pixel_addr = PIXEL_START_ADDR;
    // char temp_read[2];
    // float thermistor_value = ReadThermistor();

    // for(uint32_t pixel_index = 0; pixel_index < MAX_PIXEL_INDEX; pixel_index++)
    // {
    //     buffer->pixel[pixel_index] = ReadSinglePixel();
    // }

    // for(uint32_t pixel_index = 0; pixel_index < MAX_PIXEL_INDEX; pixel_index++)
    // {
    //     i2c.write(I2C_ADDR << 1, &pixel_addr, 1, false);
    //     i2c.read(I2C_ADDR << 1, &temp_read[0], 2 );

    //     //Convert temperature
    //     int temperature = ((temp_read[1] << 8) | temp_read[0]);
    //     if (temperature > 2047){
    //       temperature = temperature - 4096;
    //     }

    //     buffer->pixel[pixel_index] = temperature * 0.25;

    //     pixel_addr = pixel_addr + 2;
    // }
}

float GridEye::ReadSinglePixel(uint8_t pixelnum)
{
	if (pixelnum >= MAX_PIXEL_INDEX) {
		return 0.0f;
	}
	else
	{
		char temp[2];
		temp[0] = PIXEL_START_ADDR + (pixelnum*2);
		i2c.write(I2C_ADDR << 1, &temp[0], 1, false);
		i2c.read(I2C_ADDR << 1, &temp[0], 2 );
		int temperature = ((temp[1] << 8) | temp[0]);
		if (temperature > 2047){
          temperature = temperature - 4096;
        }
		float celsiusTherm = temperature*0.25;

		return celsiusTherm - pixel_offset[pixelnum];
	}
}


void GridEye::SetPixelOffset(uint32_t id, float value)
{
    pixel_offset[id] = value;
}

float GridEye::GetPixelOffset(uint32_t id)
{
    return pixel_offset[id];
}