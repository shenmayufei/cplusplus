#include <iostream>
#include <cstdlib>
#include <cstring>
#include "StackExample.h"
#include "LinkStack.hpp"

// 比较两个运算符的优先级，3为无效值
int isPrior(const char left, const char right)
{
    int a, b;
    switch(left)
    {
    case '+':
    case '-':
        a = 0;
        break;
    case '*':
    case '/':
        a = 1;
        break;
    default:
        a = -1;
    }

    switch(right)
    {
    case '+':
    case '-':
        b = 0;
        break;
    case '*':
    case '/':
        b = 1;
        break;
    default:
        b = -1;
    }

    if(a == -1 || b == -1) return -3; 
    if(a > b) return 1;
    else if(a==b) return 0;
    else return -1;
}

bool transformExpression(const char* infixExpr, struct Element ** postfixExpr, int * length)
{
    if(NULL == infixExpr) return false;

    int len = strlen(infixExpr);
    if(0 == len) return false;

    *postfixExpr = new struct Element [len];
    if(*postfixExpr == NULL) return false;

    zhaosl::LinkStack<int> stack;
    int i = 0, j = 0;
    while(i < len)
    {
        //std::cout << "input: " << infixExpr[i] << std::endl;
        if(infixExpr[i] <= '9' && infixExpr[i] >= '0')
        {
            int start = i;
            while(infixExpr[i] <= '9' && infixExpr[i] >= '0') i++;
            char * numStr = new char[i-start + 1];
            memcpy(numStr, infixExpr+start, i-start);
            memset(numStr+i-start, '\0', 1);
            //std::cout << "numStr: " << numStr << std::endl;
            (*postfixExpr)[j].value = atoi(numStr);
            (*postfixExpr)[j++].type = 4; // int
            //std::cout << "case num, add to output: " << (*postfixExpr)[j-1] << std::endl;
        }
        
        switch(infixExpr[i])
        {
        case '+':
        case '-':
        case '*':
        case '/':
            int stackTop;
            while(stack.top(stackTop) && stackTop != '(' && isPrior(stackTop, infixExpr[i]) >= 0)
            {
                stack.pop(stackTop);
                (*postfixExpr)[j].value = stackTop;
                (*postfixExpr)[j++].type = 1;  // char
                //std::cout << "case +-*/, add to output: " << (char)(*postfixExpr)[j-1] << std::endl;
            }
            stack.push(infixExpr[i]);
            break;
        case '(':
            stack.push(infixExpr[i]);
            break;
        case ')':
            if(!stack.pop(stackTop)) return false;
            while(stackTop != '(')
            {
                (*postfixExpr)[j].value =  stackTop;
                (*postfixExpr)[j++].type =  1;
                //std::cout << "case ')', add to output: " << (char)(*postfixExpr)[j-1] << std::endl;
                if(!stack.pop(stackTop)) return false;
            }
            break;
        default:
            break;
        }

        i++;
    }

    int stackTop;
    while(!stack.isEmpty())
    {
       stack.pop(stackTop);
       (*postfixExpr)[j].value = stackTop;
       (*postfixExpr)[j++].type  = 1;
    }
    *length = j;
    return true;
}

bool calculatePostfixExpress(const struct Element* postfixExpr, const int length, int * result)
{
    zhaosl::LinkStack<int> resStack;
    for(int i = 0; i < length; i++)
    {
        if(postfixExpr[i].type == 4)
            resStack.push(postfixExpr[i].value);
        else
        {
            int a, b, c;
            if(!resStack.pop(b) || !resStack.pop(a)) return false;
            
            switch(postfixExpr[i].value)
            {
            case '+':
                c = a + b;
                break;
            case '-':
                c = a - b;
                break;
            case '*':
                c = a * b;
                break;
            case '/':
                if(b==0) 
                {
                    std::cout << "cannot be divided by 0\n";
                    return false;
                }
                c = a / b;
                break;
            default:
                std::cout << "Error occured, " << (char)postfixExpr[i].value << std::endl;
                return false;
            }
            resStack.push(c);
        }
    }
    return resStack.pop(*result);
}

bool knap_recursive(int totalWeight, const int * weights, const int num)
{
    if(totalWeight== 0) return true;
    if((totalWeight < 0) || (totalWeight > 0 && num < 1)) return false;

    if(knap_recursive(totalWeight-weights[num-1], weights, num-1))
    {
        std::cout << weights[num-1] << std::endl;
        return true;
    }
    else
    {
        return knap_recursive(totalWeight, weights, num-1);
    }
}

// 背包问题，非递归实现
bool knap_nonrecur(int totalWeight, const int * weights, const int num)
{
    //zhaosl::LinkStack<KnapNode> funcStack;
    //struct KnapNode tmpNode;

    return true;
}
