// #include "MockSystemTime.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "MockSystemTime.h"
// #include "MockThermopile.h"
#include "Tracker.h"
#include "Types.h"
#include "Events.h"
#include "Queue.h"
// #include "ISystemTime.h"
#include <iostream>

using namespace std;
using ::testing::_;
using ::testing::Pointee;
using ::testing::InSequence;
using ::testing::Return;

static ImageStruct frame;

// Create mock objects
// IThermopile
class MockThermopile : public IThermopile
{
    float average;
public:
    MockThermopile() {}
    
    void ReadPixels(ImageStruct *buffer)
    {

    }

    void SetMovingAverage(bool flag) {}
    uint8_t ReadMovingAverage() { 
        return 0; 
    }
    void SetHighFrameRate(bool flag) {}
    void SetAveragePixelValue(float value)
    {
        average = value;
    }
    float ReadThermistor() {}
    float ReadSinglePixel(uint8_t pixelnum) 
    {
        // cout << "Pixel num: " << pixelnum << " value: " << frame.pixel[pixelnum] << endl;
        return frame.pixel[pixelnum];
    }
};


// class MockSystemTime : public ISystemTime {

// public:
//     uint32_t get_tick() { return 0;}
//     uint32_t get_tick_us() { return 0;}
//     uint32_t get_tick_ms() { 
//         // cout << "Tick" << endl;
//         return 500;
//     }
//     void wait(float s) {}
//     void wait_ms(uint32_t ms) {}
//     void wait_us(uint32_t us) {}
//     void reset() {}
//     uint32_t get_system_clock() { return 0;}

// };

class TrackerTests : public ::testing::Test
{
protected:
    MockThermopile dummy_thermopile;
    MockSystemTime dummy_timer;
    Queue<sEvent> event_queue;
    Tracker track_object;

    TrackerTests() : 
        event_queue(20),
        track_object(dummy_timer, dummy_thermopile, event_queue)
        {}

    void ProcessTracker(std::string filename)
    {
        ifstream file(filename,ios::in);
        // ifstream file("5JAN16 putty.log",ios::in);
        double thermistor_value = 0.0;

        EXPECT_CALL(dummy_timer, get_tick_ms()).WillRepeatedly(Return(500));

        if (file.good())
        {
            string str;
            while(getline(file, str)) 
            {
                if (str[0] == 'T')
                {
                    thermistor_value = atof(str.c_str() + 2);
                    // cout << "Thermistor: " << thermistor_value << endl;
                }
                else
                {
                    istringstream csvStream(str);
                    vector<string> csvColumn;
                    string csvElement;

                    double pixel_data;
                    double average_value = 0.0;
                    uint32_t pixel_num = 0;
                    uint32_t column = 0;
                    uint32_t row = 0;

                    while (getline(csvStream, csvElement, ','))
                    {
                        if (pixel_num % 8 == 0)
                        {
                            column++;
                            row = 0;
                        }
                        istringstream(csvElement) >> pixel_data;


                        if (pixel_data > 0.0)
                        {
                            // cout << pixel_data << endl;
                            frame.pixel[pixel_num] = pixel_data;
                            // cout << "Pixel: " << pixel_num << " Value: " << pixel_data << endl;
                            average_value += pixel_data;
                            pixel_num++;
                            row++;
                        }
                    }

                    average_value = average_value/64.0;

                    // add to the TrackerObject
                    track_object.ProcessTracker();

                    // cin.get();
                }
            }
        }
    }
    virtual void SetUp()
    {
        // ON_CALL(dummy_timer, get_tick_ms()).WillByDefault(Return(500));
    }
};


TEST_F(TrackerTests, TestMultipleObjects)
{
    track_object.Reset();
    ProcessTracker("multi_objects.txt");

    ASSERT_EQ(6, track_object.read_up_counter());
    ASSERT_EQ(6, track_object.read_down_counter());
}



TEST_F(TrackerTests, TestSingleObjects)
{
    track_object.Reset();
    ProcessTracker("single_objects.txt");

    ASSERT_EQ(3, track_object.read_up_counter());
    ASSERT_EQ(3, track_object.read_down_counter());
}
