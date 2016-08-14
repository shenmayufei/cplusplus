#ifndef _APPLE_H__
#define _APPLE_H__

#include <iostream>
#include "fruit.h"

using std::cout;
using std::endl;
using std::ostream;

class Apple: public Fruit{  
private:
  int size;
  char type;
public:
  Apple();
  Apple(int no, double weight, char key, int size, char type);
  Apple(const Apple& a);
  Apple& operator=(const Apple& a);
  virtual ~Apple();

  void save() {   }
  virtual void process(){   }

  void* operator new( size_t stAllocateBlock );
  void operator delete( void* pvMem );

  friend ostream& operator<<(ostream& os, const Apple& a);
};

inline 
Apple::Apple() : size(0), type(0) { 
  cout << "Apple::Apple()" << endl; 
}

inline
Apple::Apple(int no, double weight, char key, int size, char type) : Fruit(no, weight, key), size(size), type(type) {
    cout << "Apple::Apple(int, double, char, int, char)" << endl;
}

inline
Apple::Apple(const Apple& a):Fruit(a), size(a.size), type(a.type) { 
  cout << "Apple::Apple(const Apple&)" << endl; 
} 

inline
Apple& Apple::operator=(const Apple& a) {
  cout << "Apple::operator=" << endl;
  Fruit::operator=(a);
  this->size = a.size; 
  this->type = a.type; 
  return *this;
}

inline
Apple::~Apple() { 
  cout << "Apple::~Apple()" << endl; 
}

void* Apple::operator new( size_t stAllocateBlock ) {
    cout << "Apple::operator new( size_t )\n";
    void* pvTemp = malloc( stAllocateBlock );
    return pvTemp;
}

void Apple::operator delete( void* pvMem ) {
    cout << "Apple::opeator delete (void*)\n";
    free(pvMem);
}


ostream& operator<<(ostream& os, const Apple& a)
{
    os << "{no: " << a.Fruit::no << ", weight:" << a.Fruit::weight << ", key:" << a.Fruit::key  << ", size:" << a.size << ", type:" << a.type << "}";
    return os;
}
#endif