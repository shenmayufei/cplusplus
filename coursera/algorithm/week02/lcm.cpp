/*  
 * 4 Problem: Least Common Multiple
 *
 * Problem Introduction
 * The least common multiple of two positive integers a and b is the least positive 
 * integer m that is divisible by both a and b.
 *
 * Problem Description
 * Task. Given two integers a and b, find their least common multiple.
 * Input Format. The two integers a and b are given in the same line separated by space.
 * Constraints. 1<=a,b<=2*10^9.
 * Output Format. Output the least common multiple of a and b.
*/
#include <iostream>

long long int lcm(long long int a, long long int b);
int testlcm();

int main(int argc, char *argv[]) {
  // if(testlcm() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }

  int a, b;
  std::cin >> a >> b;
  std::cout << lcm(a, b) << std::endl;
  return 0;
}

long long int gcd(long long int a, long long int b) {
  if (a == 0) return b;
  if (a < b) {
    long long int tmp = b;
    b = a;
    a = tmp;
  }
  while(b != 0) {
    long long int tmp = b;
    b = a % b;
    a = tmp;
  } 
  return a;
}

long long int lcm(long long int a, long long int b) {
  if (a == 0 || b == 0) return 0;
  int myGcd = gcd(a, b);
  return a * (b/myGcd);
}

int testlcm() {
  long long int shouldSuccess[10][3] = {
    {6, 8, 24},
    {8, 6, 24},
    {28851538, 1183019, 1933053046},
    {1183019, 28851538, 1933053046},
    {0, 3, 0},
    {3, 0, 0}, 
    {6, 6, 6},
    {0, 0, 0},
    {14159572, 63967072, 226436590403296},
    {63967072, 14159572, 226436590403296}
  };
  for (int i = 0; i < 10 ; i++) {
    long long int res = lcm(shouldSuccess[i][0], shouldSuccess[i][1]);
    if (shouldSuccess[i][2] != res) {
      std::cout << "lcm(" << shouldSuccess[i][0] << ", " << shouldSuccess[i][1] <<  ") should be " << shouldSuccess[i][2] << ", but is " << res << std::endl;
      return -1; 
    }
  }
  return 0;
}