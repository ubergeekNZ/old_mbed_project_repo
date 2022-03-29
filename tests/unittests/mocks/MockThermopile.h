#ifndef MOCKTHERMOPILE_H
#define MOCKTHERMOPILE_H

class MockThermopile : public IThermopile
{
public:
	MOCK_METHOD1(ReadPixels, void(ImageStruct* buffer));
	MOCK_METHOD1(SetMovingAverage, void(bool flag));
	MOCK_METHOD0(ReadMovingAverage, uint8_t());
	MOCK_METHOD1(SetHighFrameRate, void(bool flag));
	MOCK_METHOD1(SetAveragePixelValue, void(float value));
	MOCK_METHOD0(ReadThermistor, float());
	MOCK_METHOD1(ReadSinglePixel, float(uint8_t pixelnum));
};


#endif