#include <iostream>
#include "List.hpp"
#include "ArrayList.hpp"
#include "LinkList.hpp"

int main(int argc, char* argv[])
{

    std::cout << "ArrayList test start\n";
    zhaosl::ArrayList<int> list1(10);
    for(int i = 0;i < 5; i++)
        list1.append(2 * i + 1);
    
    for(int i = list1.size()-1; i >= 0; i--)
    {
        
        int value;
        if(list1.getValue(i, value))
        {
            std::cout << "pos: " << i << ", value: " << value << std::endl;
        }
    }
    std::cout << "ArrayList test end\n\n";

    std::cout << "LinkList test start\n";
    zhaosl::LinkList<int> list2(10);
    for(int i = 0; i < 5; i++)
    {
        list2.append(2 * i + 1);
    }
    for(int i = list2.size() -1; i >= 0; i--)
    {
        int value;
        if(list2.getValue(i, value))
        {
            std::cout << "pos: " << i << ", value: " << value << std::endl;
        }
        else
        {
            std::cout << "pos: " << i << " not exist\n";
        }
    }
    std::cout << "LinkList test end\n\n";
    std::cout << "Exit Main function\n";
}
