#include <iostream>
#include <set>
#include <algorithm>    // std::for_each
#include <functional>   // std::bind
#include "programmer.h"

using std::set;
using std::for_each;
using std::bind;

int main(int argc, char* argv[]) {
  set<Programmer, ProgrammerIdGreater()> ps;
  ps.insert(Programmer(1, L"Scott Meyers"));
  ps.insert(Programmer(2, L"Martin Fowler"));
  ps.insert(Programmer(3, L"Bill Gates"));
  ps.insert(Programmer(4, L"P.J.Plaught"));
  ps.insert(Programmer(5, L"Stanley P.Lippman"));
  ps.insert(Programmer(6, L"Andrei Alexandrescu"));

  std::wcout << L"------------print set ---------------" << std::endl;
  for_each(ps.begin(), ps.end(), bind(&Programmer::Print));
}