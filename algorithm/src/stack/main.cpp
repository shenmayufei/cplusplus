#include <iostream>
#include "ArrayStack.hpp"
#include "LinkStack.hpp"
#include "StackExample.h"

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

    std::cout << "LinkStack test start\n";
    zhaosl::LinkStack<int> stack2;
    for(int i = 0; i < 5; i++)
        stack2.push(2*i+1);
    while(!stack2.isEmpty())
    {
        int value;
        if(stack2.pop(value))
        {
            std::cout << "link stack value: " << value << std::endl;
        }
    }
    std::cout << "LinkStack test end\n\n";

    std::cout << "Expression transform test start\n";
    const char* infixExpr = "23 + (34*45)/(5 + 6 - 7)";
    struct Element * postfixExpr;
    int length, result;
    transformExpression(infixExpr, &postfixExpr, &length); 
    std::cout << "\npost fix expression: ";
    for(int i = 0; i < length; i++)
    {
        if(postfixExpr[i].type == 1)
            std::cout << (char)postfixExpr[i].value << ", ";
        else
        {
            std::cout << postfixExpr[i].value << ", ";
        }
    }
    std::cout << std::endl;
    calculatePostfixExpress(postfixExpr, length, &result);
    std::cout << infixExpr << " = " << result << std::endl;
    std::cout << "Expression transform test end\n\n";

    std::cout << "背包问题 start\n";
    int weights[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
    int sum = 40;
    int num = 9;
    bool ok = knap_recursive(sum, weights, num);
    if(ok) std::cout << "sum = " << sum << ", num = " << num << ", weights [1-9], is ok\n";
    else std::cout << "sum = " << sum << ", num = " << num << ", weights[1-9], not ok\n";
    std::cout << "背包问题 end\n\n";

    std::cout << "Exit Main function\n";
}
