#ifndef __MYQUEUE_H__
#define __MYQUEUE_H__

#include <iostream>
#include <algorithm>

#include "MyVector_k221j976.h"

template <typename DataType>
class MyQueue : private MyVector<DataType>
{  
  private:
    size_t dataStart=-1, dataEnd=-1;

    // changes the size of the array to newSizeMyVector<DataType>(theCapacity);
    void resize(size_t newSize)
    {
        // code begins
        MyVector<DataType>::resize(newSize);
        // code ends
    }

    // requests for newCapacity amount of space
    void reserve(size_t newCapacity)
    {
        // code begins
        MyVector<DataType>::reserve(newCapacity);
        // code ends
    }

  public:

    // default constructor
    explicit MyQueue(size_t initSize = 0)
    : MyVector<DataType>(initSize)
    {
        // code begins

        // code ends
    }

    // copy constructor
    MyQueue(const MyQueue & rhs)
     : MyVector<DataType>(rhs)
    {
        // code begins

        // code ends
    }

    // move constructor
    MyQueue(MyQueue && rhs)
    : MyVector<DataType>(rhs)
    {
        // code begins

        // code ends
    }

    // destructor
    ~MyQueue()
    {
        // code begins
        MyVector<DataType>(data);
        // code ends
    }

    // copy assignment
    MyQueue & operator= (const MyQueue & rhs)
    {
        // code begins
        MyQueue copy = rhs;
        std::swap(*this, copy);
        return *this;
        // code ends
    }

    // move assignment
    MyQueue & operator= (MyQueue && rhs)
    {
        // code begins
        MyVector<DataType>(theSize);
        MyVector<DataType>(theCapacity);
        MyVector<DataType>(data);
        return *this;
        // code ends
    }

    // insert x into the queue
    void enqueue(const DataType & x)
    {
        // code begins
        MyVector<DataType>::push_back(x);
        dataEnd++;
        // code ends
    }

    // insert x into the queue
    void enqueue(DataType && x)
    {
        // code begins
        MyVector<DataType>::push_back(x);
        dataEnd++;
        // code ends
    }

    // remove the first element from the queue
    void dequeue(void)
    {
        // code begins
         MyVector<DataType>::remove(0);
        // code ends
    }

    // access the first element of the queue
    const DataType & front(void) const
    {
        // code begins
        return {MyVector<DataType>::front()};
        // code ends
    }

    // check if the queue is empty; return TRUE is empty; FALSE otherwise
    bool empty(void) const
    {
        // code begins
        return {MyVector<DataType>::empty()};
        // code ends
    }

    // access the size of the queue
    size_t size() const
    {
        // code begins
        return {MyVector<DataType>::size()};
        // code ends
    }

    // access the capacity of the queue
    size_t capacity(void) const 
    {
        // code begins
        return {MyVector<DataType>::capacity()};
        // code ends
    }

};


#endif // __MYQUEUE_H__