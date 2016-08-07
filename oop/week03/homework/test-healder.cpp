#include <iostream>
#include "header.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  Fruit f ;
  if (sizeof(f) != 24) {
    cout << "test fails, sizeof(Fruit obj) should be 24 bytes, but is "  << sizeof(f) << " bytes." << endl; 
  } else {
    cout << "test succeeds" << endl;
  }

  Apple a;
  if (sizeof(f) != 40) {
    cout << "test fails, sizeof(Apple obj) should be 40 bytes, but is "  << sizeof(f) << " bytes." << endl; 
  } else {
    cout << "test succeeds" << endl;
  }
}