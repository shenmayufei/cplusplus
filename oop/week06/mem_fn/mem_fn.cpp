// mem_fn example
#include <iostream>     // std::cout
#include <functional>   // std::mem_fn

struct int_holder {
  int value;
  int triple() {return value*3;}
  int add(int x, int y) {return x+y; }
};

int main () {
  int_holder five {5};

  // call member directly:
  std::cout << five.triple() << '\n';

  // same as above using a mem_fn:
  auto triple = std::mem_fn (&int_holder::triple);
  std::cout << triple(five) << '\n';  // 函数对象 triple 接受一个参数

  auto add = std::mem_fn (&int_holder::add);
  std::cout << add(five, 1, 2) << std::endl;  // 函数对象 add 接受三个参数

  return 0;
}