/**********************************************************
   author:     zhaosl
   created:    20150314
   purpose:    List template, 线性表基类模板
**********************************************************/
#ifndef ARRAY_LIST_TEMPLATE_H
#define ARRAY_LIST_TEMPLATE_H

#include "List.hpp"
namespace zhaosl
{
    template <typename T>
    class ArrayList : public List<T>
    {
    private:
        T * m_array;            
        int m_nCapacity;      // 顺序表的最大长度
        int m_nSize;
        int m_nPosition;
    public:
        ArrayList(const int size)
        {
            m_nCapacity = size;
            m_array = new T[size];
            m_nSize = m_nPosition = 0;
        }
    
        ~ArrayList()
        {
            delete [] m_array;
        }
        
        void clear()
        {
            delete [] m_array;
            m_nSize = m_nPosition = 0;
            m_array = new T[m_nCapacity];
        }
    
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
    int ArrayList<T>::size()
    {
        return m_nSize;
    };
    
    template <typename T>
    bool ArrayList<T>::isEmpty()
    {
        return m_nSize == 0;
    };
    
    template <typename T>
    bool ArrayList<T>::append(const T value)
    {
        if(m_nSize < m_nCapacity)
        {
            m_array[m_nSize++] = value;
            return true;
        }
        else
        {
            return false;
        }
    };

    template <typename T>
    bool ArrayList<T>::insert(const int pos, const T value)
    {
        if(m_nSize == m_nCapacity)  return false;
        if(pos < 0 || pos > m_nSize)  return false;
        for(int i = m_nSize; i > pos; i--)
        {
            m_array[i] = m_array[i-1];
        }
        m_array[pos] = value;
        m_nSize --;
        return true;
    };
    
    template <typename T>
    bool ArrayList<T>::remove(const int pos)
    {
        if(isEmpty() || pos < 0 || pos >= m_nSize) return false;
        m_nSize --;
        for(int i = pos+1; i < m_nSize; i++)
        {
            m_array[i-1] = m_array[i];
        }
        return true;
    };

    template <typename T>
    bool ArrayList<T>::getValue(const int pos, T& value)
    {
        if(pos < 0 || pos >= m_nSize) return false;
        value = m_array[pos];
        return true;
    };

    template <typename T>
    bool ArrayList<T>::setValue(const int pos, const T value) // 设置位置pos上的元素为 value
    {
        if(pos < 0 || pos >= m_nSize) return false;
        m_array[pos] = value;
        return true;
        
    };

    template <typename T>
    bool ArrayList<T>::getPos(int &pos, const T value)          // 把值为 value的元素所在位置返回到变量pos中
    {
        // 获取第一个为此值的变量
        for(int i = 0; i < m_nSize; i++)
        {
            if(value == m_array[i])
            {
                pos = i;
                return true;
            }
        }

        return false;
    }
}
#endif
