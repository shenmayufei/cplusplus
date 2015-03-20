/*******************************************************************************
 * author:          zhaosl
 * created:         20150320
 * purpose:         ArrayStack
*******************************************************************************/
#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include "Stack.hpp"
namespace zhaosl
{
    template<typename T>
    class ArrayStack : public Stack<T>
    {
    private:
        int         m_nSize;      // 栈中最多可用的元素个数
        int         m_nTop;       // 栈顶的位置，小于 m_nSize
        T           * m_pArray;   // 存放栈元素的数组
    public:
        ArrayStack();
        ArrayStack(int size);
        ~ArrayStack();
        void clear();
        bool push(const T value);
        bool pop(T & value);
        bool top(T & value);
        bool isEmpty();
        bool isFull();
    };
    
    template <typename T>
    ArrayStack<T>::ArrayStack()
    :m_nSize(0),
    m_nTop(-1),
    m_pArray(NULL)
    {
    }

    template <typename T>
    ArrayStack<T>::ArrayStack(int size)
    :m_nSize(size),
    m_nTop(-1)
    {
        m_pArray = new T[size];
    }

    template <typename T>
    ArrayStack<T>::~ArrayStack()
    {
        m_nTop = -1;
        m_nSize = 0;
        delete m_pArray;
    }

    template <typename T>
    void ArrayStack<T>::clear()
    {
        m_nTop = -1;
        m_nSize = 0;
    }

    template <typename T>
    bool ArrayStack<T>::push(const T value)
    {
        if(m_nTop >= m_nSize - 1) return false;
        m_pArray[++m_nTop] = value;
        return true;
    }

    template <typename T>
    bool ArrayStack<T>::pop(T & value)
    {
        if(m_nTop < 0) return false;
        value = m_pArray[m_nTop--];
        return true;
    }

    template <typename T>
    bool ArrayStack<T>::top(T & value)
    {
        if(m_nTop < 0) return false;
        value = m_pArray[m_nTop];
        return true;
    }

    template <typename T>
    bool ArrayStack<T>::isEmpty()
    {
        return m_nTop < 0;
    }

    template <typename T>
    bool ArrayStack<T>::isFull()
    {
        return m_nTop == m_nSize - 1;
    }
}
#endif
