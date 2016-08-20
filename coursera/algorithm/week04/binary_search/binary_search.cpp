#include <iostream>
#include <cassert>
#include <vector>

using std::vector;

int binary_search_helper(const vector<int> &a, int start, int end, int x) {
  if (start > end) return -1;
  int mid = (start+end)/2;
  if (x == a[mid]) return mid;
  
  if (x < a[mid]) return binary_search_helper(a, start, mid-1, x);
  else return binary_search_helper(a, mid+1, end, x);
}

int binary_search(const vector<int> &a, int x) {
  int left = 0, right = (int)a.size(); 
  return binary_search_helper(a, left, right-1, x);  
}

int main() {
  int n;
  std::cin >> n;
  vector<int> a(n);
  for (size_t i = 0; i < a.size(); i++) {
    std::cin >> a[i];
  }
  int m;
  std::cin >> m;
  vector<int> b(m);
  for (int i = 0; i < m; ++i) {
    std::cin >> b[i];
  }
  for (int i = 0; i < m; ++i) {
    //replace with the call to binary_search when implemented
    std::cout << binary_search(a, b[i]) << ' ';
  }
}
