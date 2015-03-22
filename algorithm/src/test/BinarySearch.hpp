/**************************************************************************
 * author:      zhaosl
 * created:     20150322
 * purpose:     测试 二分查找，找不到需要的最多次数
 **************************************************************************/
 #ifndef BINARY_SEARCH_H
 #define BINARY_SEARCH_H

namespace zhaosl
{

    template <typename T>
    int BinarySearch_help(const T * array, int start, int end, const T& key)
    {
        std::cout << "Enter BinarySearch_help, start: " << start << ", end: " << end << std::endl;
        int middle = (start + end)/2;
        if(key == array[middle]) return middle;
        else if(key < array[middle])
        {
            end = middle - 1;
            if(end < start) return -1;
            else return BinarySearch_help(array, start, end, key);
        }
        else
        {
            start = middle + 1;
            if(end < start) return -1;
            else return BinarySearch_help(array, start, end, key);
        }
    };

    template <typename T>
    int BinarySearch(const T * array, const int length, const T& key)
    {
        return BinarySearch_help(array, 0, length-1, key);
    }
}
 #endif
