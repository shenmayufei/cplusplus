/*
 * Fibonacci Numbers
 *  
 * 5 Advanced Problem: Huge Fibonacci Number modulo m
 * ( We strongly recommend you start solving advanced problems only when you are 
 * done with the basic problems.)
 *
 * Problem Introduction
 * The Fibonacci numbers are defined as follows: F0 = 0, F1 = 1, and Fi = Fi-1 + Fi-2 for i >= 2
 * 
 * Problem Description
 * Task. Given two integers n and m, output Fn mod m (that is, the remainder of Fn when divided by m).
 * Input Format. The input consists of two integers n and m given on the same line (separated by a space).
 * Constraints. 1<=n<=10^18, 2<=m<=10^5.
 * Output Format. Output Fn mod m.
*/
#include <iostream>
#include <iomanip> 
#include <vector>

long long int get_fibonaccihuge(long long int n, long long int m);
int testfib();
void generateFib();

int main(int argc, char *argv[]) {
  // if(testfib() == 0) {
  //   std::cout << "test passed" << std::endl;
  // } else {
  //   std::cout << "test failed" << std::endl;
  // }

  // generateFib();
  
    long long n, m;
    std::cin >> n >> m;
    std::cout << get_fibonaccihuge(n, m) << '\n';
    return 0;
}

long long int get_fibonaccihuge(long long int n, long long int m) {
  if (n==0) return 0;
  if (n==1) return 1;
  std::vector<long long int> fibs;
  fibs.reserve(8);
  fibs.push_back(0);
  fibs.push_back(1);
  fibs.push_back(1);
  int fibSize = 3;
  for(int i = fibSize; ; i++) {
    fibs.push_back((fibs[i-1] + fibs[i-2]) % m);
    if (fibs[i-1] == 0 && fibs[i] == 1) {
      fibSize = i-1;
      break;
    }
  }
  return fibs[n%fibSize];
}

int testfib() {
  long long int shouldSuccess[10][3] = {
    {5, 5, 0},
    {5, 3, 2},
    {5, 2, 1},
    {10, 2, 1},
    {10, 3, 1},
    {13, 2, 1},
    {13, 3, 2},
    {15, 2, 0},
    {15, 3, 1},
    {281621358815590, 30524, 11963}
  };
  for (int i = 0; i < 10 ; i++) {
    long long int res = get_fibonaccihuge(shouldSuccess[i][0], shouldSuccess[i][1]);
    if (shouldSuccess[i][2] != res) {
      std::cout << "get_fibonaccihuge(" << shouldSuccess[i][0] << ", " << shouldSuccess[i][1] <<  ") should be " << shouldSuccess[i][2] << ", but is " << res << std::endl;
      return -1; 
    }
  }
  return 0;
}

void generateFib() {
  std::cout << std::setw(7) << std::left << "i";
  for (int n = 0; n < 30; n++) {
    std::cout << std::setw(4) << std::left << n; 
  }
  std::cout << std::endl;
  for (int m = 2; m < 10; m++) {
    std::cout << std::setw(2) << std::left << "fib(" << m << ") ";
    for (int n = 0; n < 30; n++) {
      std::cout << std::setw(4) << std::left << get_fibonaccihuge(n, m);
    }
    std::cout << std::endl;
  }
}