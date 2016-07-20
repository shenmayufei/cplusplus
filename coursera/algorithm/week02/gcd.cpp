/*
 * 3 Problem: Greatest Common Divisor
 *
 * Problem Introduction
 * The greatest common divisor GCD(a; b) of two non-negative integers a and b (which are not both equal to 0) is the greatest integer d that divides both a and b.
 *
 * Problem Description
 * Task. Given two integers a and b, find their greatest common divisor.
 * Input Format. The two integers a; b are given in the same line separated by space.
 * Constraints. 1<=a,b<=2*10^9.
 * Output Format. Output GCD(a; b).
*/
#include <iostream>

int gcd(int a, int b);
int testgcd();

int main(int argc, char *argv[]) {
  // if(testgcd() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }

  int a, b;
  std::cin >> a >> b;
  std::cout << gcd(a, b) << std::endl;
  return 0;
}

int gcd(int a, int b) {
  if (a == 0) return b;
  if (a < b) {
    int tmp = b;
    b = a;
    a = tmp;
  }
  while(b != 0) {
    int tmp = b;
    b = a % b;
    a = tmp;
  } 
  return a;
}

int testgcd() {
  int shouldSuccess[10][3] = {
    {18, 35, 1},
    {0, 3, 3},
    {3, 0, 3},
    {2, 4, 2},
    {6, 9, 3},
    {9, 6, 3},
    {2, 3, 1},
    {3, 2, 1},
    {28851538, 1183019, 17657},
    {1183019, 28851538, 17657}
  };
  for (int i = 0; i < 10 ; i++) {
    int res = gcd(shouldSuccess[i][0], shouldSuccess[i][1]);
    if (shouldSuccess[i][2] != res) {
      std::cout << "gcd(" << shouldSuccess[i][0] << ", " << shouldSuccess[i][1] <<  ") should be " << shouldSuccess[i][2] << ", but is " << res << std::endl;
      return -1; 
    }
  }
  return 0;
}