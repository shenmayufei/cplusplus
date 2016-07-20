/*
 *  Fibonacci Numbers
 *
 *  1 Problem: Small Fibonacci Number
 *  Problem Introduction
 *  The Fibonacci numbers are defined as follows: F0 = 0, F1 = 1, and Fi = Fi􀀀1 + Fi􀀀2 for i  2.
 *
 *  Task. Given an integer n, find the nth Fibonacci number Fn.
 *  Input Format. The input consists of a single integer n.
 *  Constraints. 0<=n<=45.
 *  Output Format. Output Fn.
*/
#include <iostream>

long long int calc_fib(int n);
int testfib();

int main(int argc, char *argv[]) {
  // if(testfib() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }

    int n = 0;
    std::cin >> n;

    std::cout << calc_fib(n) << '\n';
    return 0;
}

long long int calc_fib(int n) {
  if (n==0) return 0;
  if (n==1) return 1;
  long long int last = 1;
  long long int current = 1;
  for(int i = 2; i < n; i++) {
    long long int tmp = current;
    current += last;
    last = tmp;
  }
  return current;
}

int testfib() {
  int shouldSuccess[10][2] = {
    {0, 0},
    {1, 1},
    {2, 1},
    {3, 2},
    {4, 3},
    {5, 5},
    {6, 8},
    {7, 13},
    {8, 21},
    {9, 34}
  };
  for (int i = 0; i < 10 ; i++) {
    long long int res = calc_fib(shouldSuccess[i][0]);
    if (shouldSuccess[i][1] != res) {
      std::cout << "calc_fib(" << shouldSuccess[i][0] << ") should be " << shouldSuccess[i][1] << ", but is " << res << std::endl;
      return -1; 
    }
  }
  return 0;
}