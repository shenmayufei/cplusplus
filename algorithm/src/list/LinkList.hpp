/**********************************************************
   author:     zhaosl
   created:    20150314
   purpose:    List template, 链表类模板
**********************************************************/
#ifndef LINK_LIST_TEMPLATE_H
#define LINK_LIST_TEMPLATE_H

#include "List.hpp"
namespace zhaosl
{
    template <typename T>
    class LinkNode
    {
    public:
        T    data;
        LinkNode<T> * next;
        LinkNode(const T info)
        {
            data = info;
            next = NULL;
        };
        LinkNode()
        {
            next = NULL;
        };
    };

    template <typename T>
    class LinkList : public List<T>
    {
    private:
        LinkNode<T> *head, *tail;
        LinkNode<T> * setPos(const int pos); // 返回线性表指向第p个元素的指针值
    public:
        LinkList(int size)
        {
            head = tail = new LinkNode<T>();
        }
    
        ~LinkList();
        void clear();
        int size();
        bool isEmpty();                     // 判空
        bool append(const T value);        // 在表尾添加一个元素value，表长度+1
        bool insert(const int pos, const T value); // 在位置 pos 插入一个元素value，表长度+1
        bool remove(const int pos);                // 删除位置pos上的元素，表长度-1
        bool getValue(const int pos, T& value);      // 读取位置pos上的元素到 value中
        bool setValue(const int pos, const T value); // 设置位置pos上的元素为 value
        bool getPos(int &p, const T value);          // 把值为 value的元素所在位置返回到变量pos中
    };
     
    template <typename T>
    LinkList<T>::~LinkList()
    {
        LinkNode<T> * tmp;
        while(NULL != head)
        {
            tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    template <typename T>
    void LinkList<T>::clear()
    {
        LinkNode<T> * tmp;
        LinkNode<T> * curr = head->next;
        while(NULL != curr)
        {
            tmp = curr;
            curr = curr->next;
            delete tmp;
        }
        head->next = NULL;
        tail = head;
    }

    template <typename T>
    int LinkList<T>::size()
    {  // O(N)
        LinkNode<T> * curr = head->next; 
        int initialSize = 0;
        while(NULL != curr)
        {
            initialSize ++;
            curr = curr->next;
        }

        return initialSize;
        
    };
    
    template <typename T>
    bool LinkList<T>::isEmpty()
    {
        return head==tail;
    };
    
    template <typename T>
    bool LinkList<T>::append(const T value)
    {
        LinkNode<T> * newNode = new LinkNode<T>(value);
        if(NULL == newNode) return false;
        tail->next = newNode;
        tail = newNode;
        return true;
    };

    template <typename T>
    bool LinkList<T>::insert(const int pos, const T value)
    {   // 头不计入位置
        if(pos < 0) return false;
        int loc = 0;
        LinkNode<T> * curr = head;
        LinkNode<T> * newNode = new LinkNode<T>(value);
        if(NULL == newNode) return false;

        while(NULL != curr)
        {
            if(loc == pos)
            {
                newNode->next = curr->next;
                curr->next = newNode;
                return true;
            }
            
            curr = curr->next;
            loc ++;
           
        }
        return false;
    };
    
    template <typename T>
    bool LinkList<T>::remove(const int pos)
    {   // O(n)
        if(pos < 0) return false;
        int loc = 0;
        LinkNode<T> * curr = head;
        while(NULL != curr->next)
        {
            if(loc == pos)
            {
               LinkNode<T> * tmp = curr->next;
               curr->next = tmp->next;
               delete tmp;
               return true;
            }

            loc ++;
            curr = curr->next;
        }
        return false;
    };

    template <typename T>
    bool LinkList<T>::getValue(const int pos, T& value)
    {
        if(pos < 0) return false;
        int loc = 0;
        LinkNode<T> * curr = head->next;
        while(NULL != curr)
        {
            if(loc == pos)
            {
                value = curr->data;
                return true;
            }
            loc ++;
            curr = curr->next;
        }
        return false;
    };

    template <typename T>
    bool LinkList<T>::setValue(const int pos, const T value) // 设置位置pos上的元素为 value
    {
        if(pos < 0) return false;
        int loc = 0;
        LinkNode<T> * curr = head->next;
        while(NULL != curr)
        {
            if(loc == pos)
            {
                curr->data = value;
                return true;
            }
            loc ++;
            curr = curr->next;
        }
        return false;
        
    };

    template <typename T>
    bool LinkList<T>::getPos(int &pos, const T value)          // 把值为 value的元素所在位置返回到变量pos中
    {
        // 获取第一个为此值的变量
        pos = 0;
        LinkNode<T> * curr = head->next;
        while(NULL != curr)
        {
            if(value == curr->data)
            {
                return true;
            }
            pos ++;
            curr = curr->next;
        }
        return false;
    }
}
#endif
