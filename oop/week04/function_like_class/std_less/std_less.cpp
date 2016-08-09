// less example (http://www.cplusplus.com/reference/functional/less/)
#include <iostream>     // std::cout
#include <functional>   // std::less
#include <algorithm>    // std::sort, std::includes

int main () {
  // 简单的例子, 表达式 "std::less<int>()" 创建了一个临时对象  
  int a = 5, b = 4;
  std::cout << "std::less<int>()(" << a << ", " << b << "): " << std::less<int>()(a, b) << std::endl;
  std::cout << "std::less<int>()(" << b << ", " << a << "): " << std::less<int>()(b, a) << std::endl;

  std::cout << "std::less_equal<int>()(" << a << ", " << b << "): " << std::less_equal<int>()(a, b) << std::endl;
  std::cout << "std::less_equal<int>()(" << b << ", " << a << "): " << std::less_equal<int>()(b, a) << std::endl;
  std::cout << "std::less_equal<int>()(" << a << ", " << a << "): " << std::less_equal<int>()(a, a) << std::endl;

  // 网站上带的高级例子
  int foo[]={10,20,5,15,25};
  int bar[]={15,10,20};
  std::sort (foo, foo+5, std::less<int>());  // 5 10 15 20 25
  std::sort (bar, bar+3, std::less<int>());  //   10 15 20
  if (std::includes (foo, foo+5, bar, bar+3, std::less<int>()))
    std::cout << "foo includes bar.\n";
  return 0;
}
