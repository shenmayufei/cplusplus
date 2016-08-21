#include <iostream>
#include <cstdlib>
#include <ctime>
#include "find_if_not_equal_to.h"
#include "person.h" 

template<typename T>
void printVector(const vector<T>& a) {
  std::cout << "[";
  for(typename vector<T>::const_iterator it = a.begin(); it != a.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

template<typename T>
int countNoneZero(const vector<T>& a) {
  int count = 0;
  const T zero = T();
  for (typename vector<T>::const_iterator it = a.begin(); it != a.end(); it++) {
    if (*it != zero) count ++;
  } 
  return count;
}


int testInt() {
  int maxtests = 1000;
  while(maxtests-->0) {
    vector<int> a;
    size_t vecSize = rand() % 10 + 1;
    a.reserve(vecSize);
    for (size_t i = 0;i < vecSize; i++) a.push_back(rand() % 10-5);
    
    clock_t t = clock();
    auto b = find_if_not_equal_to(a);
    t = clock() - t;
    printf ("find_if_not_equal_to cost %lu clicks (%f milli seconds).\n",t,((float)t)/CLOCKS_PER_SEC * 1000);
    // std::cout << "a: ";
    // printVector(a);
    // std::cout << "b: ";
    // printVector(b);
    // std::cout << std::endl;

    int count = countNoneZero(a);
    if (b.size() != count) {
      std::cout << "b.size(): " << b.size() << ", but the number of none zero elements in a should be " << count << std::endl;
      std::cout << "a: ";
      printVector(a);
      std::cout << "b: ";
      printVector(b);
      return 1;
    } 
  }
  return 0;
}

int testCustomizedType() {
  int maxtests = 1000;
  while(maxtests-->0) {
    vector<Person> a;
    size_t vecSize = rand() % 10 + 1;
    a.reserve(vecSize);
    for (size_t i = 0;i < vecSize; i++) {
      if (rand()%10 == 0) a.push_back(Person());
      else a.push_back(Person("hahah", rand()%100));
    }
    
    clock_t t = clock();
    auto b = find_if_not_equal_to(a);
    t = clock() - t;
    printf ("find_if_not_equal_to cost %lu clicks (%f milli seconds).\n",t,((float)t)/CLOCKS_PER_SEC * 1000);
    // std::cout << "a: ";
    // printVector(a);
    // std::cout << "b: ";
    // printVector(b);
    // std::cout << std::endl;

    int count = countNoneZero(a);
    if (b.size() != count) {
      std::cout << "b.size(): " << b.size() << ", but the number of none zero elements in a should be " << count << std::endl;
      std::cout << "a: ";
      printVector(a);
      std::cout << "b: ";
      printVector(b);
      return 1;
    } 
  }
  return 0;
}

int main(int argc, char* argv[]) {
  if (testInt() != 0) std::cout << "test fails" << std::endl;
  else std::cout << "test succeeds" << std::endl;


  // if (testCustomizedType() != 0) std::cout << "test fails" << std::endl;
  // else std::cout << "test succeeds" << std::endl;
}