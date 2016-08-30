#ifndef __PROGRAMMER_H_
#define __PROGRAMMER_H_

#include <string>
#include <iostream>
#include <functional>

using std::wstring;

class ProgrammerIdGreater;
class ProgrammerNameLess;

class Programmer {
private:
  int Id;
  wstring Name;
public:
  Programmer(const int id,const wstring name): Id(id), Name(name) {}

  bool operator==(const Programmer& p) const {return p.Id == Id && p.Name == Name; }
  void setName(const wstring name) { Name = name; }

  void Print() const {
    std::wcout << L"[" << Id << L"]:" << Name << std::endl;
  }

  friend class ProgrammerIdGreater;
  friend class ProgrammerNameLess;
};

class ProgrammerIdGreater {
public:
  bool operator() (const Programmer& x, const Programmer& y) const {return x.Id > y.Id;}
};

class ProgrammerNameLess {
public:
  bool operator() (const Programmer& x, const Programmer& y) const {return x.Name < y.Name;}
};

// http://stackoverflow.com/questions/33114656/replacement-for-binary-function
#endif