#ifndef _PERSON_H__
#define _PERSON_H__

#include <iostream>
#include <string>

using std::string;
using std::ostream;

class Person {
private:
  string name;
  int age;
public:
  Person():name("no name"), age(0) {}
  Person(string name, int age): name(name), age(age) {}
  bool operator == (const Person& p) const {return name==p.name && age == p.age; }
  bool operator != (const Person& p) const {return name!=p.name || age != p.age; }
  friend ostream& operator << (ostream& os, const Person& p);
};

ostream& operator << (ostream& os, const Person& p) {
  return os << "{name:\"" << p.name << "\", age:"<< p.age << "}";
}

#endif