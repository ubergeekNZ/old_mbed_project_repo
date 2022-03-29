// #include "MockSystemTime.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Settings.h"
#include "Types.h"
#include "Queue.h"
#include "Events.h"
#include <iostream>

using namespace std;
using ::testing::_;
using ::testing::Pointee;
using ::testing::InSequence;
using ::testing::Return;



class CommandParserTests : public ::testing::Test
{
protected:


    CommandParserTests() {}

    virtual void SetUp()
    {

    }
};

TEST_F(CommandParserTests, TestEvents)
{

}

TEST_F(CommandParserTests, TestStates)
{

}
