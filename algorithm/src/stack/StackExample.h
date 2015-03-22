/******************************************************************************
 * author:      zhaosl
 * created:     20150321
 * purpose:     栈的应用，1. 表达式转换求值, 只支持int 2. 背包问题，递归、非递归
******************************************************************************/
#ifndef STACK_EXAMPLE_H
#define STACK_EXAMPLE_H
struct Element
{
    int type; // 1-char, 2-short, 4-int
    int value;
};

struct KnapNode
{
    int sum;  // 剩余重量
    int type; // 情况类型 0. 成功; 1. s-w[n-1], n-1 ; 2. s, n-1
};

bool transformExpression(const char* infixExpression, struct Element ** postfixExpression, int *length);
bool calculatePostfixExpress(const struct Element * postfixExpression, const int length, int * result);

// 背包问题，递归实现
bool knap_recursive(int totalWeight, const int * weights, const int num);
// 背包问题，非递归实现
bool knap_nonrecur(int totalWeight, const int * weights, const int num);
#endif
