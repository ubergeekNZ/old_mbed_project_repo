#ifndef GRIDEYE_H
#define GRIDEYE_H
 
#include "mbed.h"
#include "IThermopile.h"
#include "Types.h"
#include "Queue.h"
#include "ISystemTick.h"

#define I2C_ADDR            0x68 
#define THERML_ADDR         0x0E
#define THERMH_ADDR         0x0F
#define FRAMERATE_ADDR		0x02
#define AVE_ADDR			0x07
#define PIXEL_START_ADDR    0x80
#define MAX_PIXEL_INDEX     64
#define THRESHOLD_OFFSET	2.2f

class GridEye : public IThermopile {
protected:        
    I2C i2c;
    bool threshold;
    float pixel_offset[MAX_PIXEL_INDEX];
public:
    GridEye(PinName sda, PinName scl);
    void SetThreshold(bool flag);
	void SetHighFrameRate(bool flag);
	void SetMovingAverage(bool flag);
	uint8_t ReadMovingAverage();
    float ReadThermistor();
    void ReadPixels(ImageStruct *buffer); // need to change this
    float ReadSinglePixel(uint8_t pixelnum);
    void SetPixelOffset(uint32_t id, float value);
    float GetPixelOffset(uint32_t id);
};

#endif  // GRIDEYE_H
 