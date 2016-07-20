#include <iostream>

int main(){
  int a = 0;
  int b = 0;
  int sum = 0;
  std::cin >> a;
  std::cin >> b;
  sum = a + b;
  std::cout << sum;
  return 0;
}

// compile: g++ -pipe -O2 starter.cpp -lm