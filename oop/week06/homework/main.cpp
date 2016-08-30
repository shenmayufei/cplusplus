#include <iostream>
#include <set>
#include <algorithm>    // std::for_each
#include <functional>   // std::bind
#include "programmer.h"


void testIdCompare() {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

  std::set<Programmer, ProgrammerIdGreater > ps;
  ps.insert(Programmer(1, L"Scott Meyers"));
  ps.insert(Programmer(2, L"Martin Fowler"));
  ps.insert(Programmer(3, L"Bill Gates"));
  ps.insert(Programmer(4, L"P.J.Plaught"));
  ps.insert(Programmer(5, L"Stanley P.Lippman"));
  ps.insert(Programmer(6, L"Andrei Alexandrescu"));

  std::wcout << L"------------print set order by id ---------------" << std::endl;
  auto printFunc = std::bind(&Programmer::Print, _1);
  std::for_each(ps.begin(), ps.end(), printFunc);
}

void testNameCompare() {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...
  std::set<Programmer, ProgrammerNameLess > ps;
  ps.insert(Programmer(1, L"Scott Meyers"));
  ps.insert(Programmer(2, L"Martin Fowler"));
  ps.insert(Programmer(3, L"Bill Gates"));
  ps.insert(Programmer(4, L"P.J.Plaught"));
  ps.insert(Programmer(5, L"Stanley P.Lippman"));
  ps.insert(Programmer(6, L"Andrei Alexandrescu"));

  std::wcout << L"------------print set order by name---------------" << std::endl;
  auto printFunc = std::bind(&Programmer::Print, _1);
  std::for_each(ps.begin(), ps.end(), printFunc);
}

void testFindEqualTo() {
  using namespace std::placeholders;    // adds visibility of _1, _2, _3,...

  std::set<Programmer, ProgrammerIdGreater > ps;
  ps.insert(Programmer(1, L"Scott Meyers"));
  ps.insert(Programmer(2, L"Martin Fowler"));
  ps.insert(Programmer(3, L"Bill Gates"));
  ps.insert(Programmer(4, L"P.J.Plaught"));
  ps.insert(Programmer(5, L"Stanley P.Lippman"));
  ps.insert(Programmer(6, L"Andrei Alexandrescu"));

  std::wcout << L"----------trying to find out {3, L\"Bill Gates\"}--------" << std::endl;
  
  const Programmer bill(3, L"Bill Gates");
  std::set<Programmer, ProgrammerIdGreater>::iterator it = ps.find(bill);
  if (it == ps.end()) {
    std::wcout << "cannot find bill, trying to modify it" << std::endl;
  } else {
    std::wcout << "found bill:                                     ";
    it->Print();
    // static_cast will get a copy of the object, not the object itself
    static_cast<Programmer>(*it).setName(L"David Vandevoorde");
    std::wcout << "<static_case> after trying to change the object:";
    it->Print();
    std::wcout << "<const_cast>  after trying to change the object:";
    // const_cast get a reference to the object itself, so modify succeeds
    const_cast<Programmer&>(*it).setName(L"David Vandevoorde");
    it->Print();
    std::wcout << std::endl;

    std::wcout << "after modify" << std::endl;
    auto printFunc = std::bind(&Programmer::Print, _1);
    std::for_each(ps.begin(), ps.end(), printFunc);
  }
}

int main(int argc, char* argv[]) {
  testIdCompare();
  std::wcout << std::endl;

  testFindEqualTo();
  std::wcout << std::endl;

  testNameCompare();
}


