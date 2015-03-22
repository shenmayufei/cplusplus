/**************************************************************************
 * author:      zhaosl
 * created:     20150322
 * purpose:     顺序存储结构实现的队列
 * note:        空队列: m_pFront == m_pRear;
 *              满队列: m_pFront = (m_pRear+1) % m_nCapacity
**************************************************************************/
#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H
//#include <iostream>
#include "QueueBase.hpp"

namespace zhaosl
{
    template <typename T>
    class QueueNode
    {
    public:
        T      data;
        QueueNode<T> * next;
        QueueNode(const T value)
        :data(value)
        {
            next = NULL;
        }
    };

    template <typename T>
    class LinkQueue : public BaseQueue<T>
    {
    private:
        int                 m_nSize;
        QueueNode<T>        * m_pFront;
        QueueNode<T>        * m_pRear;

    public:
        LinkQueue();
        ~LinkQueue();
        
        void clear();
        bool enqueue(const T value);
        bool dequeue(T & value);
        bool front(T & value);
        bool isEmpty();
        int  size();
    };

    template <typename T>
    LinkQueue<T>::LinkQueue()
    :m_nSize(0)
    ,m_pFront(NULL)
    ,m_pRear(NULL)
    {
    }

    template <typename T>
    LinkQueue<T>::~LinkQueue()
    {
        QueueNode<T>  * curr;
        while(NULL != m_pFront)
        {
           curr = m_pFront;
           m_pFront = m_pFront->next;
           delete curr;
        }
    }

    template <typename T>
    void LinkQueue<T>::clear()
    {
        QueueNode<T>   * curr;
        while(NULL != m_pFront)
        {
            curr = m_pFront;
            m_pFront = m_pFront->next;
            delete curr;
        }
        m_pRear = NULL;
        m_nSize = 0;
    }

    template <typename T>
    bool LinkQueue<T>::enqueue(const T value)
    {
        QueueNode<T>  * tmpNode = new QueueNode<T>(value);
        if(NULL == tmpNode) return false;
        if(NULL == m_pRear) m_pFront = m_pRear = tmpNode;
        else
        {
            //std::cout << "add " << value << " into the queue\n";
            m_pRear->next = tmpNode;
            m_pRear = tmpNode;
        }
        m_nSize++;
        return true;
    }

    template <typename T>
    bool LinkQueue<T>::dequeue(T & value)
    {
        //std::cout << "m_pFront is NULL: " << (m_pFront==NULL) << std::endl;
        if(isEmpty()) return false;
        value = m_pFront->data;
        //std::cout << "value: " << m_pFront->data << std::endl; 
        QueueNode<T> * tmpNode = m_pFront;
        m_pFront = m_pFront->next;
        m_nSize--;
        delete tmpNode;
        return true;
    }

    template <typename T>
    bool LinkQueue<T>::front(T & value)
    {
        if(isEmpty()) return false;
        value = m_pFront->data;
        return true;
    }

    template <typename T>
    bool LinkQueue<T>::isEmpty()
    {
        return m_pFront == NULL;
    }

    template <typename T>
    int LinkQueue<T>::size()
    {
        return m_nSize;
    }

}
#endif
