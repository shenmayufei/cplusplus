#ifndef _FRUIT_H_
#define _FRUIT_H_

#include <iostream>

using std::cout;
using std::endl;
using std::ostream;

class Fruit{
protected:
  int no;
  double weight;
  char key;
public:
  Fruit();
  Fruit(int no, double weight, char key);
  Fruit(const Fruit& f);
  Fruit& operator=(const Fruit& f);
  virtual ~Fruit();

  virtual void process(){   }

  friend ostream& operator<<(ostream& os, const Fruit& a);
};
inline
Fruit::Fruit() : no(0), weight(0.0), key(0) { 
  cout << "Fruit::Fruit()" << endl; 
}

inline 
Fruit::Fruit(int no, double weight, char key): no(no), weight(weight), key(key) {
  cout << "Fruit::Fruit(int, double, char)" << endl; 
}

inline
Fruit::Fruit(const Fruit& f) : no(f.no), weight(f.weight), key(f.key) {
  cout << "Fruit::Fruit(const Fruit&)" << endl; 
}

inline
Fruit& Fruit::operator=(const Fruit& f) { 
  cout << "Fruit::operator=(const Fruit&)" << endl; 
  no = f.no; 
  weight = f.weight; 
  key = f.key; 
  return *this; 
}
    
inline
Fruit::~Fruit() { 
  cout << "Fruit::~Fruit()" << endl; 
}

ostream& operator<<(ostream& os, const Fruit& a)
{
    os << "{no: " << a.no << ", weight:" << a.weight << ", key:" << a.key << "}";
    return os;
}
#endif
