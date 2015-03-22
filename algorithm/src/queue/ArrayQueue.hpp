/**************************************************************************
 * author:      zhaosl
 * created:     20150322
 * purpose:     顺序存储结构实现的队列
 * note:        空队列: m_nFront == m_nRear;
 *              满队列: m_nFront = (m_nRear+1) % m_nCapacity
**************************************************************************/
#ifndef ARRAY_QUEUE_H
#define ARRAY_QUEUE_H
#include "QueueBase.hpp"

namespace zhaosl
{
    template <typename T>
    class ArrayQueue : public BaseQueue<T>
    {
    private:
        T * m_pArray;
        int     m_nCapacity;
        int     m_nSize;
        int     m_nFront;
        int     m_nRear;

    public:
        ArrayQueue();
        ArrayQueue(int size);
        ~ArrayQueue();
        
        void clear();
        bool enqueue(const T value);
        bool dequeue(T & value);
        bool front(T & value);
        bool isEmpty();
        bool isFull();
    };

    template <typename T>
    ArrayQueue<T>::ArrayQueue()
    :m_nCapacity(128)
    ,m_nSize(0)
    ,m_nFront(0)
    ,m_nRear(0)
    {
        m_pArray = new T [m_nCapacity];
    }

    template <typename T>
    ArrayQueue<T>::ArrayQueue(int size)
    : m_nCapacity(size+1)
    , m_nSize(0)
    , m_nFront(0)
    , m_nRear(0)
    {
        m_pArray = new T[m_nCapacity];
    }

    template <typename T>
    ArrayQueue<T>::~ArrayQueue()
    {
        delete m_pArray;
    }

    template <typename T>
    void ArrayQueue<T>::clear()
    {
        m_nSize = 0;
        m_nFront = m_nRear = 0;
    }

    template <typename T>
    bool ArrayQueue<T>::enqueue(const T value)
    {
        if(isFull()) return false;
        m_pArray[m_nRear] = value;
        m_nRear = (m_nRear+1) % m_nCapacity;
        return true;
    }

    template <typename T>
    bool ArrayQueue<T>::dequeue(T & value)
    {
        if(isEmpty()) return false;
        value = m_pArray[m_nFront];
        m_nFront = (m_nFront + 1) % m_nCapacity;
        return true;
    }

    template <typename T>
    bool ArrayQueue<T>::front(T & value)
    {
        if(isEmpty()) return false;
        value = m_pArray[m_nFront];
        return true;
    }

    template <typename T>
    bool ArrayQueue<T>::isEmpty()
    {
        return m_nFront==m_nRear;
    }

    template <typename T>
    bool ArrayQueue<T>::isFull()
    {
        return m_nFront == (m_nRear+1) % m_nCapacity;
    }
}
#endif
