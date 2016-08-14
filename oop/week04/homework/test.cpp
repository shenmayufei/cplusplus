#include <iostream>
#include "apple.h"

using std::cout;
using std::endl;

void testConstructor();
void testOperatorNew();

int main(int argc, char *argv[]) {
  testConstructor();
  cout << "--------------- 测试真正结束 -----------------" << endl;

  // testOperatorNew();
}

// 函数是变量的一个作用域， 析构函数在函数退出时调用
void testConstructor() {
  cout << "---- test contructor and desctructor start -----\n";
  const Apple a;
  cout << "a = " << a << endl << endl;

  Apple b(a);
  cout << "b = " << b << endl << endl;

  Apple* c = new Apple(5, 1.0, 'c', 5, 'd');
  cout << "*c = " << *c << endl;
  delete c;
  cout << endl;

  Fruit* f = new Apple();
  cout << "*f = " << *f << endl;
  delete f;
  cout << endl;
  cout << "---- test contructor and desctructor finish ----\n";
}

void testOperatorNew() {
  cout << "---- test operator new/delete start -----\n";
  cout << endl << endl;
  cout << "use customized version of operator new/delete:\n";
  Apple* a = new Apple(5, 1.0, 'c', 5, 'd');
  delete a;
  cout << endl << endl;
  cout << "use global default version of operator new/delete:\n";
  Apple* b = ::new Apple(5, 1.0, 'c', 5, 'd');
  ::delete b;
  cout << endl << endl;

  // inheritance, ensure that Apple is desctructed correctly
  cout << "\nunder inheritance, use customized version of operator new/delete:\n"; 
  Fruit* c = new Apple(5, 1.0, 'c', 5, 'd');
  delete c;
  cout << endl << endl;

  cout << "under inheritance, use global default version of operator new/delete:\n";
  Fruit* d = ::new Apple(5, 1.0, 'c', 5, 'd');
  ::delete d;
  cout << endl << endl;
  
  cout << "---- test operator new/delete finish ----\n\n";

}
