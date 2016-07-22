#include<iostream>
#include "rectangle.h"

int main(int argc, char *argv[]) {
  Rectangle r1(4, 3, 0, 0);
  Rectangle r2(r1);
  Rectangle r3 = r2;

  std::cout << "r1 "; 
  r1.print();
  std::cout << std::endl;
  std::cout << "r2 "; 
  r2.print();
  std::cout << std::endl;
  std::cout << "r3 "; 
  r3.print();
  std::cout << std::endl;
}