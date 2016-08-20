#include <algorithm>
#include <iostream>
#include <sstream>
#include <iomanip>
#include <vector>
#include <string>
#include <cmath>

using std::vector;
using std::string;
using std::pair;
using std::min;
using std::swap;

template<typename T>
void printVector(const vector<T>& a) {
  std::cout << "[";
  for(auto it = a.begin(); it != a.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

double minimal_distance_slow(vector<int> x, vector<int> y) {
  if (x.size() <= 1) return 0;
  double min = sqrt(pow(x[0]-x[1], 2) + pow(y[0]-y[1], 2));
  size_t vecSize = x.size();
  for (size_t i = 0; i < vecSize; i++) {
    for (size_t j = i+1; j < vecSize; j++) {
      double temp = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
      if (min > temp) min = temp;
    }
  }
  return min;
}

pair<int,int> partition3(vector<int>& x, vector<int>& y, int l, int r) {
  int xx = x[l];
  int yy = y[r];

  int j = l;
  int m = l;
  for (int i = l + 1; i <= r; i++) {
    if (x[i] < xx && y[i] << yy) {
      j++;
      swap(x[i], x[j]);
      swap(y[i], y[j]);
    } else if ( (x[i]>= xx && y[i]<=yy) || (x[i] <= xx && y[i] >= yy) ){  // put all x at the head of the array
      j++;
      swap(x[i], x[j]);
      swap(y[i], y[j]);
      m++;
      swap(x[j], x[m]);
      swap(y[j], y[m]);
    }
  }
  pair<int, int> res(j-m+l, j);
  for(int i = m-l; i>=0 && l+i < j; i--,j--) {  // move all x at the head to the middle
    swap(x[l+i], x[j]);
    swap(y[l+i], y[j]);
  }
  return res;
}

double minimal_distance_helper(vector<int> x, vector<int> y, int l, int r) {
  std::cout << "l:" << l << ", r:" << r << std::endl;
  if (l >= r) return 0;
  if (l+1 == r) return sqrt(pow(x[l]-x[r], 2) + pow(y[l]-y[r], 2));

  pair<int, int> m = partition3(x, y, 0, x.size()-1);

  std::cout << "l:" << l  << ", m:" << m.first << ", m1:" << m.second << ", r:" << r << std::endl;
  double minNow;
  if (m.first > l && m.second < r) {
    double minLeft = minimal_distance_helper(x, y, l, m.first - 1);
    double minMid = minimal_distance_helper(x, y, m.first, m.second);
    double minRight = minimal_distance_helper(x, y, m.second + 1, r);

    minNow = std::min(std::min(minLeft, minMid), minRight);
  }

  for(int i = l; i < m.first; i++) {
    for(int j = m.first; j <= m.second; j++) {
      double min = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
      if (minNow > min) minNow = min;
    }

    for (int j = m.second + 1; j <= r; j++) {
      double min = sqrt(pow(x[i]-x[j], 2) + pow(y[i]-y[j], 2));
      if (minNow > min) minNow = min;
    }
  }

  return minNow;
}


double minimal_distance(vector<int> x, vector<int> y) {
  return minimal_distance_helper(x, y, 0, x.size()-1);
}

int test() {
  while(true) {
    vector<int> x, y;
    size_t vecSize = rand() % 10 + 1;
    for (size_t i = 0; i < vecSize; i++) {
      x.push_back(rand() % 1000);
      y.push_back(rand() % 1000);
    }

    clock_t t, t1, t2;

    t = clock();
    double minSlow = minimal_distance_slow(x, y);
    t1 = clock();
    double min = minimal_distance(x, y);
    t2 = clock();

    t2 = t2 - t1;
    t1 = t1 -t;
    printf ("minimal_distance_slow cost %lu clicks (%f milli seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC * 1000);
    printf ("minimal_distance      cost %lu clicks (%f milli seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC * 1000);
    std::cout << std::endl;

    if (minSlow != min) {
      std::cout << "should be " << minSlow << ", but is " << min << std::endl;
      printVector(x);
      printVector(y);
      return 1;
    }
  }
  return 0;
}

int main() {
  // size_t n;
  // std::cin >> n;
  // vector<int> x(n);
  // vector<int> y(n);
  // for (size_t i = 0; i < n; i++) {
  //   std::cin >> x[i] >> y[i];
  // }
  // std::cout << std::fixed;
  // std::cout << std::setprecision(9) << minimal_distance(x, y) << "\n";

  if (test() != 0) std::cout << "test fails" << std::endl;
}
