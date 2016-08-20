#include <algorithm>
#include <iostream>
#include <vector>
#include <map>
#include <utility>

using std::pair;
using std::vector;
using std::map;

int get_majority_element_slow(const vector<int>& a, int left, int right) {
  if (left == right) return -1;
  if (left + 1 == right) return -1;

  map<int, size_t> freq;
  for (size_t i = left; i < right; i++) {
    map<int, size_t>::iterator it = freq.find(a[i]);
    if (it == freq.end()) freq[a[i]] = 1;
    else freq[a[i]]++;
  }
  size_t half = (right - left )/ 2;
  for (map<int, size_t>::const_iterator it = freq.begin(); it != freq.end(); it++) {
    if (it->second > half) return 1;
  }
  return -1;
}

// return value <number, frequency>
pair<int, int> get_majority_element_helper(vector<int>& a, int left, int right){
  if (left >= right) return pair<int,int>(0, 0);
  if (left+1 == right) {
    if (a[left] == a[right]) return pair<int, int>(a[left], 2);
    else return pair<int, int>(0, 0);
  }

  int mid = (left+right)/2;
  pair<int, int> resLeft = get_majority_element_helper(a, left, mid);
  pair<int, int> resRight = get_majority_element_helper(a, mid, right);

  // std::cout << "left: " << left  << ", major:" << resLeft.first << ", freq:" << resLeft.second << std::endl;
  // std::cout << ", right:" << right << ", major:" << resRight.first << ", freq:"  << resRight.second << std::endl;

  if (resLeft.first == resRight.first) return pair<int, int>(resLeft.first, resLeft.second + resRight.second);
  else if (resLeft.second > resRight.second) return pair<int, int>(resLeft.first, resLeft.second - resRight.second);
  else if (resLeft.second == resRight.second) return pair<int, int>(0, 0);
  else return pair<int, int>(resRight.first, resRight.second - resLeft.second);
}

int get_majority_element(vector<int> &a, int left, int right) {
  pair<int, int> res = get_majority_element_helper(a, left, right);
  if (res.second == 0) return -1;
  
  int major = res.first;
  int count = 0;
  for (int i = left; i < right; i++) {
    if (a[i] == major) count++;
  }
  if (count > (right-left)/2) return 1;
  return -1;
}

void printVector(const vector<int>& a) {
  std::cout << "[";
  for(vector<int>::const_iterator it = a.begin(); it != a.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

int test() {
  size_t vecSize = 100000 / (rand()+1);
  while(true) {
    vector<int> vec;
    for (size_t i = 0; i < vecSize; i++) vec.push_back(1000000000/(rand()+1));

    clock_t t, t1, t2;

    t = clock();
    int slowRes = get_majority_element_slow(vec, 0, vec.size());
    t1 = clock();
    int fastRes = get_majority_element(vec, 0, vec.size());
    t2 = clock();

    t2 = t2 - t1;
    t1 = t1 -t;
    printf ("slow version cost %lu clicks (%f milli seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC * 1000);
    printf ("fast version cost %lu clicks (%f milli seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC * 1000);
    std::cout << std::endl;

    if (slowRes != fastRes) {
      std::cout << "fast res: " << fastRes << ", slow res:" << slowRes << std::endl;
      std::cout << "arr: ";
      printVector(vec);

      return 1;
    }
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  std::cout << (get_majority_element_slow(a, 0, a.size()) != -1) << '\n';


  // if (test() != 0) {
  //   std::cout << "test fails" << std::endl;
  // }
}
