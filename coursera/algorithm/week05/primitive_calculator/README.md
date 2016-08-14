## Problem Introduction
You are given a primitive calculator that can perform the following three operations with the current number
x: multiply x by 2, multiply x by 3, or add 1 to x. Your goal is given a positive integer n, find the
minimum number of operations needed to obtain the number n starting from the number 1.

## Problem Description

**Task.** Given an integer n, compute the minimum number of operations needed to obtain the number n
starting from the number 1.

**Input Format.** The input consists of a single integer 1 ≤ n ≤ 106
.

**Output Format.** In the first line, output the minimum number k of operations needed to get n from 1.
In the second line output a sequence of intermediate numbers. That is, the second line should contain
positive integers a0, a2, . . . , ak−1 such that a0 = 1, ak−1 = n and for all 0 ≤ i < k − 1, ai+1 is equal to
either ai + 1, 2ai
, or 3ai
. If there are many such sequences, output any one of them.


Attention: when n=10, greedy does not work.