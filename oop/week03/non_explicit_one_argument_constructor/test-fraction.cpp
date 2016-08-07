#include <iostream>
#include "fraction.h"

int main(int argc, char * argv[]) {
  Fraction f(3, 5);
  Fraction d =  f + 4;  // here 4 is converted to a Fraction(4, 1), 4+f is not allowed
  std::cout << "d = " << d << std::endl;
}