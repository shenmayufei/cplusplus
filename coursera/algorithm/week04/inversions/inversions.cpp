#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;

void printVector(const vector<long long>& a) {
  std::cout << "[";
  for(vector<long long>::const_iterator it = a.begin(); it != a.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

template<typename T>
long long get_number_of_inversions_slow(const vector<T>& a) {
  long long number_of_inversions = 0;
  for (size_t i = 0;i < a.size()-1; i++) {
    for (size_t j = i+1; j < a.size(); j++) {
      if (a[i] > a[j]) number_of_inversions++;
    }
  }
  return number_of_inversions;
}

template<typename T>
long long get_number_of_inversions(vector<T> &a, vector<T> &b, size_t left, size_t right) {
  long long number_of_inversions = 0;
  if (right <= left + 1) return number_of_inversions;
  size_t ave = left + (right - left) / 2;
  number_of_inversions += get_number_of_inversions(a, b, left, ave);
  number_of_inversions += get_number_of_inversions(a, b, ave, right);
  //write your code here
  int k = left;
  int i = left, j = ave;
  while(i < ave && j < right) {
    while (a[i] <= a[j]) {
      b[k++] = a[i++];
      if (i >= ave) break;
    } 
    while(a[j] < a[i]) {
      number_of_inversions += ave - i;   // next swap shall reduce inversions by ave-i
      b[k++] = a[j++];
      if (j >= right) break;
    }
  }
  while (i < ave) {
    b[k++] = a[i++];
  }
  while (j < right) {
    b[k++] = a[j++];
  }
  for (int i = left; i < right; i++) {
    // std::cout << "left: " << left << ", right:" << right << ", ave:" << ave << std::endl;
    // printVector(b);
    a[i] = b[i];
  }
  return number_of_inversions;
}

int test() {
  size_t vecSize = 10000;
  int maxTime = 1000;
  while(maxTime-- > 0 ) {
    vector<long long> vec;
    for (size_t i = 0; i < vecSize; i++) vec.push_back(rand()%10);
    vector<long long> vecB(vec);
    vector<long long> backup(vec);

    clock_t t, t1, t2;

    t = clock();
    long long inverseCountSlow = get_number_of_inversions_slow(vec);
    t1 = clock();
    long long inverseCountFast = get_number_of_inversions(vec, vecB, 0, vec.size());
    t2 = clock();

    t2 = t2 - t1;
    t1 = t1 -t;
    printf ("slow counting cost %lu clicks (%f milli seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC * 1000);
    printf ("fast counting cost %lu clicks (%f milli seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC * 1000);
    std::cout << std::endl;

    if (inverseCountSlow != inverseCountFast) {
      std::cout << "inverse count should be " << inverseCountSlow << ", but is " << inverseCountFast << std::endl;
      std::cout << "before: ";
      printVector(backup);
      std::cout << std::endl;
      std::cout << "after : ";
      printVector(vec);
      std::cout << std::endl;
      return 1;
    }
  }
  return 0;
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  vector<int> b(a.size());
  std::cout << get_number_of_inversions(a, b, 0, a.size()) << '\n';

  // if (0 != test()) {
  //   std::cout << "test fails" << std::endl;
  // }
}
