#include <iostream>
#include "fraction.h"

int main(int argc, char * argv[]) {
  Fraction f(3, 5);
  double d = 4 + f;
  std::cout << "d = " << d << std::endl;
}