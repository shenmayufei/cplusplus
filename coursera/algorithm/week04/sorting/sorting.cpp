#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using std::vector;
using std::swap;
using std::pair;

int partition2(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] <= x) {
      j++;
      swap(a[i], a[j]);
    }
  }
  swap(a[l], a[j]);
  return j;
}

pair<int,int> partition3(vector<int> &a, int l, int r) {
  int x = a[l];
  int j = l;
  int m = l;
  for (int i = l + 1; i <= r; i++) {
    if (a[i] < x) {
      j++;
      swap(a[i], a[j]);
    } else if (a[i]== x) {  // put all x at the head of the array
      j++;
      swap(a[i], a[j]);
      m++;
      swap(a[j], a[m]);
    }
  }
  pair<int, int> res(j-m+l, j);
  for(int i = m-l; i>=0 && l+i < j; i--,j--) {  // move all x at the head to the middle
    swap(a[l+i], a[j]);
  }
  return res;
}

void randomized_quick_sort_two_partions(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  int m = partition2(a, l, r);

  randomized_quick_sort_two_partions(a, l, m - 1);
  randomized_quick_sort_two_partions(a, m + 1, r);
}

void randomized_quick_sort(vector<int> &a, int l, int r) {
  if (l >= r) {
    return;
  }

  int k = l + rand() % (r - l + 1);
  swap(a[l], a[k]);
  pair<int,int> m = partition3(a, l, r);

  randomized_quick_sort(a, l, m.first - 1);
  randomized_quick_sort(a, m.second + 1, r);
}

void printVector(const vector<int>& a) {
  std::cout << "[";
  for(vector<int>::const_iterator it = a.begin(); it != a.end(); it++) {
    std::cout << *it << ", ";
  }
  std::cout << "]\n";
}

int testSorting() {
  while(true) {
    vector<int> src;
    for (int i = 0; i < 10000 ; i++)  src.push_back(rand() % 100);
    vector<int> srcBak(src);

    // std::cout << "before: ";
    // printVector(src);

    clock_t t, t1, t2;

    t = clock();
    randomized_quick_sort_two_partions(src, 0, src.size() -1);
    t1 = clock();
    randomized_quick_sort(srcBak, 0, srcBak.size()-1);
    t2 = clock();

    for (int i = 0; i < src.size(); i++) {
      if (src[i] != srcBak[i]) {
        std::cout << "i: " << i << ", src[i]: " << src[i] << " should equals to srcBak[i]: " << srcBak[i] << std::endl;
        std::cout << "src after  two partition sort: ";
        printVector(src);
        std::cout << "src after three partition sort:";
        printVector(srcBak);
        return 1;
      }
    }

    // std::cout << "after:  ";
    // printVector(src);

    t2 = t2 - t1;
    t1 = t1 -t;
    printf ("2 partition sorting cost %lu clicks (%f milli seconds).\n",t1,((float)t1)/CLOCKS_PER_SEC * 1000);
    printf ("3 partition sorting cost %lu clicks (%f milli seconds).\n",t2,((float)t2)/CLOCKS_PER_SEC * 1000);
    std::cout << std::endl;
  }
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cin >> a[i];
  }
  randomized_quick_sort(a, 0, a.size() - 1);
  for (size_t i = 0; i < a.size(); ++i) {
    std::cout << a[i] << ' ';
  }


  // pressure testing, data set is size 10^4, 
  // it's 60x faster than merge sort
  // if (testSorting() != 0) {
  //   std::cout << "test fails" << std::endl;
  // }
}
