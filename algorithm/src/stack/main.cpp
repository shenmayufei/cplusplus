#include <iostream>
#include "ArrayStack.hpp"

int main(int argc, char* argv[])
{

    std::cout << "ArrayStack test start\n";
    zhaosl::ArrayStack<int> stack1(10);
    for(int i = 0;i < 5; i++)
        stack1.push(2 * i + 1);
    
    while(!stack1.isEmpty())
    {
        int value;
        if(stack1.pop(value))
        {
            std::cout << "stack value: " << value << std::endl;
        }
    }
    std::cout << "ArrayStack test end\n\n";

    std::cout << "Exit Main function\n";
}
