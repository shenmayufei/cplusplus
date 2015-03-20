/*******************************************************
 * author:      zhasl
 * created:     20150320
 * purpose:     Stack template, 栈基类模板
*******************************************************/
#ifndef STACK_H
#define STACK_H

namespace zhaosl
{
    template <typename T>
    class Stack
    {
    public:
        void clear();          // 变为空栈
        bool push(const T item);   // 入栈，成功返回true，失败返回false
        bool pop(T & value);    // 弹出栈顶内容到 value，成功返回true，失败返回false
        bool top(T & value);   // 获取栈顶内容，空栈时返回false，获取失败返回false
        bool isEmpty();
        bool isFull();  

    };
}

#endif
