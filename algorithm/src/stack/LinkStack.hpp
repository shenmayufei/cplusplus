/*******************************************************************************
 * author:          zhaosl
 * created:         20150320
 * purpose:         LinkStack 链式栈
*******************************************************************************/
#ifndef LINK_STACK_H
#define LINK_STACK_H

#include "Stack.hpp"
namespace zhaosl
{
    template <typename T>
    class StackNode
    {
    public:
        T       data;
        StackNode<T> * next;
        StackNode(const T value)
        {
            data = value;
            next = NULL;
        }
    };

    template<typename T>
    class LinkStack : public Stack<T>
    {
    private:
        StackNode<T>        * m_pTop;       // 栈顶的位置
    public:
        LinkStack();
        ~LinkStack();
        void clear();
        bool push(const T value);
        bool pop(T & value);
        bool top(T & value);
        bool isEmpty();
    };
    
    template <typename T>
    LinkStack<T>::LinkStack()
    :m_pTop(NULL)
    {
    }

    template <typename T>
    LinkStack<T>::~LinkStack()
    {
        clear();
    }

    template <typename T>
    void LinkStack<T>::clear()
    {
        StackNode<T> * curr;
        while(NULL != m_pTop)
        {
           curr = m_pTop;
           m_pTop = m_pTop->next;
           delete curr;
        }
    }

    template <typename T>
    bool LinkStack<T>::push(const T value)
    {
        if(NULL == m_pTop)
        {
            m_pTop = new StackNode<T>(value);
            if(NULL == m_pTop) return false;
        }
        else
        {
            StackNode<T> * tmpNode = new StackNode<T>(value);
            if(NULL == tmpNode) return false;
            tmpNode->next = m_pTop;
            m_pTop = tmpNode;
        }
        return true;
        
    }

    template <typename T>
    bool LinkStack<T>::pop(T & value)
    {
        if(NULL == m_pTop) return false;
        value = m_pTop->data;
        StackNode<T> * tmpNode = m_pTop;
        m_pTop = m_pTop->next;
        delete tmpNode;
        return true;
    }

    template <typename T>
    bool LinkStack<T>::top(T & value)
    {
        if(NULL == m_pTop) return false;
        value = m_pTop->data;
        return true;
    }

    template <typename T>
    bool LinkStack<T>::isEmpty()
    {
        return NULL==m_pTop;
    }

}
#endif
