#include <iostream>
#include "ArrayQueue.hpp"
#include "LinkQueue.hpp"

int main(int argc, char * argv[])
{
    //const char * str1 = "abcdefg";
    //const char * str2 = "zyx";

    //printf("aaa: %s,bbb: %s, ccc: %d\n", str1, str2);

    std::cout << "ArrayQueue test start\n";
    zhaosl::ArrayQueue<int> arrQueue;
    for(int i = 0;i < 5; i++)  arrQueue.enqueue(2 * i + 1);
    int value = 0;
    while( !arrQueue.isEmpty())
    {
        arrQueue.dequeue(value);
        std::cout << value << ", ";
    }
    std::cout << std::endl;
    std::cout << "ArrayQueue test end\n\n";

    std::cout << "LinkQueue test start\n";
    zhaosl::LinkQueue<int> lnkQueue;
    for(int i = 0;i < 5; i++)
    {
        lnkQueue.enqueue(2 * i + 1);
        std::cout << "enqueue " << 2 * i + 1 << ", queue size: " << lnkQueue.size() << std::endl;
    }
    while( !lnkQueue.isEmpty())
    {
        lnkQueue.dequeue(value);
        std::cout << value << ", ";
    }   
    std::cout << std::endl;
    std::cout << "LinkQueue test end\n\n";
    return 0;
}
