/*************************************************************************
 * author:          zhaosl
 * created:         20150322
 * purpose:         kmp match, KMP字符匹配算法
*************************************************************************/
#ifndef KMP_MATCH_H
#define KMP_MATCH_H
#include <string>
#include <assert.h>

int * findNext(std::string pattern)
{
    int i = 0;
    int k = -1;
    int m = pattern.length();       // m 为字符串 pattern 的长度
    assert(m > 0);   
    int * next = new int [m];
    assert(NULL != next);
    next[0] = -1;

    while(i < m)
    {
        while(k >= 0 && pattern[i] != pattern[k])  // 求最大首尾字符串
        {
            k = next[k];
        }

        i++;
        k++;
        if(i == m) break;
        if(pattern[i] == pattern[k])  next[i] = next[k];  // 
        else                          next[i] = k;
    }
    return next;
}

int kmp(const std::string & target, const std::string & pattern, int * Next)
{
    int i = 0;              // 模式的下表变量
    int j = 0;              // 目标的下标变量
    int pLen = pattern.length();  // 模式串的长度
    int tLen = target.length();   // 目标串的长度
    if(tLen < pLen) return -1;   // 匹配失败

    while(i < pLen && j < tLen)
    {
        if(i == -1 || target[j] == pattern[i])
            i++, j++;
        else  i = Next[i];
    }

    if( i >= pLen)  return j-pLen+1;
    else            return -1;
}

#endif
