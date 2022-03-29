#include "gmock/gmock.h"
#include "gtest/gtest.h"
#include "Queue.h"
#include <iostream>

using namespace std;

using ::testing::_;
using ::testing::InSequence;
using ::testing::Return;
using ::testing::NiceMock;

class QueueTests : public::testing::Test
{
protected:

    const int queue_size = 100;
    const int elements_to_add = 20;
    Queue<int> p_queue;

    QueueTests() : p_queue(queue_size) {}
    virtual void SetUp()
    {
        for (uint8_t i = 0; i < elements_to_add; i++)
        {
            p_queue->enqueue(i);
        }
    }
};

TEST_F(QueueTests, Dequeue)
{
    for (uint8_t i = 0; i < elements_to_add; i++)
    {
        ASSERT_EQ(i, p_queue->dequeue());
    }
}

TEST_F(QueueTests, Peek)
{
    ASSERT_EQ(0, p_queue->peek());

    ASSERT_EQ(0, p_queue->dequeue());
}

TEST_F(QueueTests, GetSize)
{
    ASSERT_EQ(queue_size, p_queue->getSize());
}

TEST_F(QueueTests, GetCount)
{
    ASSERT_EQ(elements_to_add, p_queue->getCount());

    int x = elements_to_add +1;
    p_queue->enqueue(x);

    ASSERT_EQ(elements_to_add + 1, p_queue->getCount());

    (void)p_queue->dequeue();
    (void)p_queue->dequeue();

    ASSERT_EQ(elements_to_add - 1, p_queue->getCount());
}

TEST_F(QueueTests, FullAndReset)
{
    ASSERT_EQ(false, p_queue->isFull());
    ASSERT_EQ(false, p_queue->isEmpty());

    int size_to_fill = p_queue->getSize() - p_queue->getCount();
    for (int i = 0; i < size_to_fill; i++)
    {
        p_queue->enqueue(i);
    }

    ASSERT_EQ(true, p_queue->isFull());
    ASSERT_EQ(false, p_queue->isEmpty());
    ASSERT_EQ(p_queue->getSize(), p_queue->getCount());   

    p_queue->reset();

    ASSERT_EQ(false, p_queue->isFull());
    ASSERT_EQ(true, p_queue->isEmpty());
    ASSERT_EQ(0, p_queue->getCount());    
}


// TEST_F(QueueTests, EnqueueAndDequeue)
// {
//     ASSERT_EQ(false, p_queue->isFull());
//     ASSERT_EQ(false, p_queue->isEmpty());

//     int size_to_fill = p_queue->getSize() - p_queue->getCount();
//     for (int i = 0; i < size_to_fill; i++)
//     {
//         p_queue->enqueue(i);
//     }

//     ASSERT_EQ(true, p_queue->isFull());
//     ASSERT_EQ(false, p_queue->isEmpty());
//     ASSERT_EQ(p_queue->getSize(), p_queue->getCount());   

//     p_queue->dequeue();
//     p_queue->enqueue(666);

//     for (int i = 0; i < p_queue->getSize(); i++)
//     {
//         cout << p_queue->dequeue() << endl;
//     }
// }