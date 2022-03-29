#ifndef IQueue_H
#define IQueue_H

#include <stdint.h>
#include <stdlib.h>

/*! \file */

/** \addtogroup queue
 *  @{
 */
template<class T>
class IQueue
{
public:
    /**
     * @brief Determines if the queue is empty
     */
    virtual bool isEmpty() = 0;

    /**
     * @brief Determines if the queue is full
     */
    virtual bool isFull() = 0;

    /**
     * @brief Adds the given item to the back of the queue
     * 
     * @param item Reference to the item to add to the queue
     */
    virtual void enqueue(const T& item) = 0;

    /**
     * @brief Removes the item at the front of the queue and returns it
     * @return Item that was removed from the queue
     */
    virtual T dequeue() = 0;

    /**
     * @brief Returns the item at the front of the queue without removing it
     * @return Copy of the item at the front of the queue
     */
    virtual T& peek() = 0;

    /**
     * @brief Resets the queue to its default state
     */
    virtual void reset() = 0;

    /**
     * @brief Gets the maximum size of the queue
     */
    virtual uint32_t getSize(void) = 0;

    /**
     * @brief Gets the number of elements currently in the queue
     */
    virtual uint32_t getCount(void) = 0;
};

/** @}*/
#endif  // IQueue_H
