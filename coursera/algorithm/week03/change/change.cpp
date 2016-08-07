/*
 * Changing Money
 *  
 * 2 Problem: The Last Digit of a Large Fibonacci Number
 * Task. The goal in this problem is to find the minimum number 
 *   of coins needed to change the input value (an integer) into coins 
 *   with denominations 1, 5, and 10
 * Input Format. The input consists of a single integer m.
 * Constraints. 1<= m <=10^3.
 * Output Format. Output the minimum number of coins with denominations 1, 5, 10 that changes m.
*/

#include <iostream>

int testChange();

int get_change(int m) {
  //write your code here
  int n = 0;
  if (m >= 10) {
    n += m / 10;
    m %= 10;
  }
  if (m >= 5) {
    n += m / 5;
    m %= 5;
  }
  n += m;
  return n;
}

int main() {
  // if (0 == testChange()) std::cout << "test passed" << std::endl;
  // else std::cout << "test fails" << std::endl;

  int m;
  std::cin >> m;
  std::cout << get_change(m) << '\n';
}


int testChange() {
  int shouldSuccess[5][2] = {
    {0, 0},
    {1, 1},
    {2, 2},
    {3, 3},
    {28, 6}
  };
  for (int i = 0; i < 5; i++) {
    int res = get_change(shouldSuccess[i][0]); 
    if (res != shouldSuccess[i][1]) {
      std::cout << "get_change(" << shouldSuccess[i][0] << ") should be " << shouldSuccess[i][1] << ", but is " << res << std::endl;
      return 1;
    }
  }
  return 0;
}
