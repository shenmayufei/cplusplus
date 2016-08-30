#include <iostream>
#include "my_numeric_limits.h"

int main(int argc, char* argv[]) {
  std::wcout << L"max int:   " << Calculator<int>::GetLimit() << std::endl;
  std::wcout << L"max long:  " << Calculator<long>::GetLimit() << std::endl;
  std::wcout << L"max float: " << Calculator<float>::GetLimit() << std::endl;
  std::wcout << L"max double:" << Calculator<double>::GetLimit() << std::endl;
}