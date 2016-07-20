#include<iostream>
#include "date.h"

void testIsLeapYear();

int main(int argc, char *argv[]) {
  Date *dates = CreatePoints();
  std::cout << "before sorting: " << std::endl;
  for (int i = 0; i < 10 ;i ++) {
    dates[i].print();
  }
  Sort(dates, 10);
  std::cout << "\nafter sorting:" << std::endl;
  for (int i = 0;i < 10; i++) {
    dates[i].print();
  }
  delete []dates;
}


void testIsLeapYear() {
  int shouldSuccess[5] = {0, 1900, 2000, 2015, 2016};
  bool results[5] = {true, false, true, false, true};
  bool success = true;
  for (int i=0;i < 5; i++) {
    if (isLeapYear(shouldSuccess[i]) != results[i]) {
      success = false;
      std::cout << "isLeapYear(" << shouldSuccess[i] << ") should return " << results[i] << ", but not" << std::endl;
    }
  }
  if (success)  std::cout << "testIsLeapYear, test passed" << std::endl;
  else          std::cout << "testIsLeapYear, test failed" << std::endl;
}