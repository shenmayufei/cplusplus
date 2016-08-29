#ifndef __PROGRAMMER_H_
#define __PROGRAMMER_H_

#include <string>
#include <iostream>

using std::wstring;

class ProgrammerIdGreater;

class Programmer {
private:
  int Id;
  wstring Name;
public:
  Programmer(const int id,const wstring name): Id(id), Name(name) {}

  void Print() const {
    std::wcout << L"[" << Id << L"]:" << Name << std::endl;
  }
  friend class ProgrammerIdGreater;
};

class ProgrammerIdGreater {
  bool operator() (const Programmer& x, const Programmer& y) const {return x.Id > y.Id;}
};

// http://stackoverflow.com/questions/33114656/replacement-for-binary-function
#endif