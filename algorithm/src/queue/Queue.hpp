/**************************************************************************
 * author: zhaosl
 * created: 20150322
 * purpose: 队列的基类模板
***************************************************************************/
#ifndef BASE_QUEUE_H
#define BASE_QUEUE_H
namespace zhaosl
{
    template <typename T>
    class Queue<T>
    {
    public:
        void clear();
        bool enqueue(const T value); // 加到队尾
        bool dequeue(T & value);     // 将队头出队
        bool front(T & value);       // 获取队列头元素，但不出队
        bool isEmpty();              // 队列是否为空
    };
}
#endif
