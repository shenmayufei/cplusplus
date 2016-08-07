#include <iostream>
#include "header.h"

using std::cout;
using std::endl;

int main(int argc, char *argv[]) {
  // first check the length of base types, to verify the system
  cout << "sizeof(char): " << sizeof(char) << endl;
  cout << "sizeof(int) : " << sizeof(int) << endl;
  cout << "sizeof(long): " << sizeof(long) << endl;
  cout << "sizeof(double): " << sizeof(double) << endl;
  cout << "sizeof(void *): " << sizeof(void *) << endl;

  bool is64Bit = sizeof(void *) == 8;

  if (is64Bit) {
    if (sizeof(Fruit) != 32) {
      cout << "test fails, sizeof(Fruit obj) should be 32 bytes, but is "  << sizeof(Fruit) << " bytes." << endl; 
    } else {
      cout << "test succeeds" << endl;
    }

    if (sizeof(Apple) != 40) {
      cout << "test fails, sizeof(Apple obj) should be 40 bytes, but is "  << sizeof(Apple) << " bytes." << endl; 
    } else {
      cout << "test succeeds" << endl;
    }
  } else {
    if (sizeof(Fruit) != 16) {
      cout << "test fails, sizeof(Fruit obj) should be 16 bytes, but is "  << sizeof(Fruit) << " bytes." << endl; 
    } else {
      cout << "test succeeds" << endl;
    }

    if (sizeof(Apple) != 24) {
      cout << "test fails, sizeof(Apple obj) should be 24 bytes, but is "  << sizeof(Apple) << " bytes." << endl; 
    } else {
      cout << "test succeeds" << endl;
    }
  }
}