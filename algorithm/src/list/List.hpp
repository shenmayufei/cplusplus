/**********************************************************
   author:     zhaosl
   created:    20150314
   purpose:    List template, 线性表基类模板
**********************************************************/
#ifndef LIST_TEMPLATE_H
#define LIST_TEMPLATE_H
namespace zhaosl
{
    template <typename T>
    class List
    {
        void clear();                       // 置空线性表
        bool isEmpty();                     // 判空
        bool append(const T value);        // 在表尾添加一个元素value，表长度+1
        bool insert(const int pos, const T value); // 在位置 pos 插入一个元素value，表长度+1
        bool remove(const int pos);                // 删除位置pos上的元素，表长度-1
        bool getValue(const int pos, T& value);      // 读取位置pos上的元素到 value中
        bool setValue(const int pos, const T value); // 设置位置pos上的元素为 value
        bool getPos(int &p, const T value);          // 把值为 value的元素所在位置返回到变量pos中
    };
    
}
#endif
