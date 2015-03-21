/******************************************************************************
 * author:      zhaosl
 * created:     20150321
 * purpose:     栈的应用，1. 表达式转换求值
******************************************************************************/
#ifndef STACK_EXAMPLE_H
#define STACK_EXAMPLE_H
struct Element
{
    int type; // 1-char, 2-short, 4-int
    int value;
};
bool transformExpression(const char* infixExpression, struct Element ** postfixExpression, int *length);
bool calculatePostfixExpress(const struct Element * postfixExpression, const int length, int * result);

#endif
