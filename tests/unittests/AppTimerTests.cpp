#include "List.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "AppTimer.h"
#include "MockSystemTime.h"
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace std; 

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

#define MAX_LIST_SIZE        256
#define NUM_TEST_RUN         100


class AppTimerTests : public ::testing::Test
{
protected:
    MockSystemTime mock_systime;
    AppTimer timer;
    TimerId timerIds[10];

    AppTimerTests() : timer(mock_systime, 10) {}

    void CreateTimers()
    {
        for (int i = 0; i < 10; i++)
        {
           timerIds[i] = timer.CreateTimer(100 + i, TIME_MS);
        }
    }

    void TestExpiry()
    {
        EXPECT_CALL(mock_systime, get_tick_ms()).WillRepeatedly(Return(1));

        // Wait for timer expires
        for (int j = 0; j < 99; j++)
        {
            EXPECT_CALL(mock_systime, reset());
            timer.Process();
        }

        for (int j = 0; j < 11; j++)
        {
           EXPECT_CALL(mock_systime, reset());
           // Check if timers has expired
           for (int i = 0; i < 10; i++)
           {
               if (i < j)
               {
                    ASSERT_EQ(1, timer.Expired(timerIds[i]));
               }
               else
               {
                   ASSERT_EQ(0, timer.Expired(timerIds[i]));
               }

           }
           timer.Process();
        }
    }

    virtual void SetUp()
    {
        
    }
};

TEST_F(AppTimerTests, CheckTimerExpires)
{
    CreateTimers();
    TestExpiry();
}

TEST_F(AppTimerTests, CheckTimerReload)
{
    CreateTimers();
    TestExpiry();

    for (int j = 0; j < NUM_TEST_RUN; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            timer.Reload(timerIds[i], 100 + i, TIME_MS);
        }

        TestExpiry();
    }
}

TEST_F(AppTimerTests, CheckTimerDelete)
{
    CreateTimers();
    TestExpiry();

    for (int j = 0; j < NUM_TEST_RUN; j++)
    {
        for (int i = 0; i < 10; i++)
        {
            timer.Reload(timerIds[i], 100 + i, TIME_MS);
        }

        TestExpiry();
    }

    for (int i = 0; i < 10; i++)
    {
        ASSERT_EQ(10-i, timer.GetNumberTimers());
        timer.Delete(timerIds[i]);
    }
}
