#include <iostream>
#include "List.hpp"

int main(int argc, char* argv[])
{
    zhaosl::ArrayList<int> list1(10);
    for(int i = 0;i < 5; i++)
        list1.append(2 * i + 1);
    
    for(int i = list1.size()-1; i >= 0; i--)
    {
        
        int value;
        if(list1.getValue(i, value))
        {
            std::cout << "pos: i, value: " << value << std::endl;
        }
    }
    std::cout << "Exit Main function\n";
}
