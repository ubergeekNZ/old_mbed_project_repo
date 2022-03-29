#include "Frame.h"
#include <time.h>
#include <stdlib.h>
#include <iostream>
#include "gmock/gmock.h"
#include "gtest/gtest.h"

using namespace std; 

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;

class FrameTests : public ::testing::Test
{
protected:

    Frame<uint32_t> *test_frame; 

    FrameTests() {}

    virtual void SetUp()
    {
        test_frame = new Frame<uint32_t>(8, 8);
    }
};

TEST_F(FrameTests, TestGetSetElements)
{
    uint32_t value = 0;
    
    // populate frame
    for (uint32_t y = 0; y < 8; y++)
    {
        for (uint32_t x = 0; x < 8; x++)
        {
            test_frame->set_pixel_value(x, y, value);
            value++;
        }
    }

    // retrieve frame and compare
    value = 0;
    for (uint32_t y = 0; y < 8; y++)
    {
        for (uint32_t x = 0; x < 8; x++)
        {
            ASSERT_EQ(test_frame->get_pixel_value(x, y), value);
            value++;
        }
    }
}

TEST_F(FrameTests, TestCopyFrame)
{
    // create a new dummy frame
    Frame<uint32_t> *dummy_frame = new Frame<uint32_t>(8,8);

    // populate dummy frame
    uint32_t value = 0;
    for (uint32_t y = 0; y < 8; y++)
    {
        for (uint32_t x = 0; x < 8; x++)
        {
            dummy_frame->set_pixel_value(x, y, value);
            value++;
        }
    }

    // copy dummy frame to the test frame
    test_frame = dummy_frame;
    
    // retrieve frame and compare
    value = 0;
    for (uint32_t y = 0; y < 8; y++)
    {
        for (uint32_t x = 0; x < 8; x++)
        {
            ASSERT_EQ(test_frame->get_pixel_value(x, y), value);
            value++;
        }
    }
}

// TEST_F(FrameTests, TestSubtractingFrame)
// {
//     // create a new dummy frame
//     Frame<uint32_t> *dummy_frame = new Frame<uint32_t>(8,8);

//     // populate dummy frame
//     uint32_t value = 1;
//     for (uint32_t y = 0; y < 8; y++)
//     {
//         for (uint32_t x = 0; x < 8; x++)
//         {
//             dummy_frame->set_pixel_value(x, y, value);
//             value++;
//         }
//     }

//     // populate test frame
//     value = 1;
//     for (uint32_t y = 0; y < 8; y++)
//     {
//         for (uint32_t x = 0; x < 8; x++)
//         {
//             test_frame->set_pixel_value(x, y, value);
//             value++;
//         }
//     }

//     test_frame = test_frame - dummy_frame;
    
//     // retrieve frame and compare
//     value = 0;
//     for (uint32_t y = 0; y < 8; y++)
//     {
//         for (uint32_t x = 0; x < 8; x++)
//         {
//             ASSERT_EQ(test_frame->get_pixel_value(x, y), value);
//             value++;
//         }
//     }
// }

// TEST_F(FrameTests, TestAddingFrame)
// {

// }

TEST_F(FrameTests, TestDeallocation)
{
    test_frame->deallocate();
    delete test_frame;
    test_frame = NULL;

    ASSERT_FALSE(test_frame);
}

