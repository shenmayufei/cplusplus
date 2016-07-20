/*
 * Fibonacci Numbers
 *  
 * 2 Problem: The Last Digit of a Large Fibonacci Number
 * Task. Given an integer n, find the last digit of the nth Fibonacci number Fn (that is, Fn mod 10).
 * Input Format. The input consists of a single integer n.
 * Constraints. 0<=n<=10^7.
 * Output Format. Output the last digit of Fn.
*/
#include <iostream>

long long int get_fibonacci_last_digit(int n);
int testfib();

int main(int argc, char *argv[]) {
  // if(testfib() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }

    int n = 0;
    std::cin >> n;

    std::cout << get_fibonacci_last_digit(n) << '\n';
    return 0;
}

long long int get_fibonacci_last_digit(int n) {
  if (n==0) return 0;
  if (n==1) return 1;
  long long int last = 1;
  long long int current = 1;
  for(int i = 2; i < n; i++) {
    long long int tmp = current;
    current += last;
    current %= 10;
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
    {7, 3},
    {8, 1},
    {327305, 5}
  };
  for (int i = 0; i < 10 ; i++) {
    long long int res = get_fibonacci_last_digit(shouldSuccess[i][0]);
    if (shouldSuccess[i][1] != res) {
      std::cout << "get_fibonacci_last_digit(" << shouldSuccess[i][0] << ") should be " << shouldSuccess[i][1] << ", but is " << res << std::endl;
      return -1; 
    }
  }
  return 0;
}