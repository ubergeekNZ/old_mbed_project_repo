#ifndef INC_QUEUE_H_
#define INC_QUEUE_H_

#include <stdint.h>
#include <stdlib.h>
#include "IQueue.h"

/*! \file */

/** \addtogroup queue
 *  @{
 */
template<class T>
class Queue : public IQueue<T>
{
private:
    uint32_t head;
    uint32_t tail;
    uint32_t count;
    uint32_t queue_size;
    T *array;
public:

    /**
     * @brief Constructs the queue with a given size
     * @param Max number of elements in the queue
     */
    explicit Queue(uint32_t size);

    /**
     * @brief Determines if the queue is empty
     */
    bool isEmpty();

    /**
     * @brief Determines if the queue is full
     */
    bool isFull();

    /**
     * @brief Adds the given item to the back of the queue
     * 
     * @param item Reference to the item to add to the queue
     */
    void enqueue(const T& item);

    /**
     * @brief Removes the item at the front of the queue and returns it
     * @return Item that was removed from the queue
     */
    T dequeue();

    /**
     * @brief Returns the item at the front of the queue without removing it
     * @return Copy of the item at the front of the queue
     */
    T& peek();

    /**
     * @brief Resets the queue to its default state
     */
    void reset();

    /**
     * @brief Gets the maximum size of the queue
     */
    uint32_t getSize(void);

    /**
     * @brief Gets the number of elements currently in the queue
     */
    uint32_t getCount(void);
};

/** @}*/

template<class T>
Queue<T>::Queue(uint32_t size): head(0), tail(0), count(0)
{
    array = new T[size++];
    queue_size = size;
}

template<class T>
bool Queue<T>::isEmpty()
{
    if (head == tail)
      return true;
    else
      return false;
}

template<class T>
bool Queue<T>::isFull()
{
    if ((tail == queue_size - 1 && head == 0) || (head == tail + 1))
      return true;
    else
      return false;
}

template<class T>
void Queue<T>::enqueue(const T& item)
{
    array[tail % queue_size] = item;
    tail++;
    count++;
}

template<class T>
T Queue<T>::dequeue()
{
    T item = array[head % queue_size];
    head++;
    count--;
    return item;
}

template<class T>
T& Queue<T>::peek()
{
    T& item = array[head % queue_size];
    return item;
}

// reset list
template<class T>
void Queue<T>::reset()
{
    head = 0;
    tail = 0;
    count = 0;
}

template<class T>
uint32_t Queue<T>::getSize(void)
{
    return queue_size - 1;
}

template<class T>
uint32_t Queue<T>::getCount(void)
{
    return count;
}

#endif  // INC_QUEUE_H_
