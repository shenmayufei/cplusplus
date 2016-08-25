// source: http://www.cplusplus.com/reference/functional/bind/
// bind example
#include <iostream>     // std::cout
#include <functional>   // std::bind

// a function: (also works with function object: std::divides<double> my_divide;)
double my_divide (double a, double b) {return a/b;}
double my_add_three(double a, double b, double c) {return a + b + c;}
double my_add_four(double a, double b, double c, double d) { return a + b + c + d; }

struct MyPair {
  double a,b;
  double multiply() {return a*b;}
};

int main () {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

  // binding functions:
  auto fn_five = std::bind (my_divide,10,2);               // returns 10/2
  std::cout << fn_five() << '\n';                          // 5

  auto fn_half = std::bind (my_divide,_1,2);               // returns a/2
  std::cout << fn_half(10) << '\n';                        // 5

  auto fn_invert = std::bind (my_divide,_2,_1);            // returns b/a
  std::cout << fn_invert(10,2) << '\n';                    // 0.2

  auto fn_rounding = std::bind<int> (my_divide,_1,_2);     // returns int(a/b)
  std::cout << fn_rounding(10,3) << '\n';                  // 3

  auto fn_add_two = std::bind<double>(my_add_three, _1, _2, 3); // returns a+b+3
  std::cout << fn_add_two(1, 2) << '\n';                        // 6

  auto fn_add_three = std::bind<double>(my_add_three, _1, _2, _3); // returns a+b+c
  std::cout << fn_add_three(1, 2, 3) << '\n';                      // 6

  auto fn_add_three_2 = std::bind<double>(my_add_four, _1, _2, _3, 0); // return a+b+c+0
  std::cout << fn_add_three_2(1, 2, 3) << '\n';                        // 6

  MyPair ten_two {10,2};

  // binding members:
  auto bound_member_fn = std::bind (&MyPair::multiply,_1); // returns x.multiply()
  std::cout << bound_member_fn(ten_two) << '\n';           // 20

  auto bound_member_data = std::bind (&MyPair::a,ten_two); // returns ten_two.a
  std::cout << bound_member_data() << '\n';                // 10

  return 0;
}