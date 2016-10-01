#include <iostream>
#include <vector>
#include <algorithm>

using std::vector;
using std::ios_base;
using std::cin;
using std::cout;

class TreeOrders {
  int n;
  vector <int> key;
  vector <int> left;
  vector <int> right;

public:
  void read() {
    cin >> n;
    key.resize(n);
    left.resize(n);
    right.resize(n);
    for (int i = 0; i < n; i++) {
      cin >> key[i] >> left[i] >> right[i];
    }
  }


  vector <int> in_order() {
    vector<int> result;
    in_order_helper(result, 0);
    return result;
  }

  void in_order_helper(vector<int>& result, int root) {
    if (root == -1) return;
    if (left[root] != -1) in_order_helper(result, left[root]);
    result.push_back(key[root]);
    if (right[root] != -1) in_order_helper(result, right[root]);
  }

  vector <int> pre_order() {
    vector<int> result;    
    pre_order_helper(result, 0);
    return result;
  }

  void pre_order_helper(vector<int>& result, int root) {
    if (root == -1) return;
    result.push_back(key[root]);
    if (left[root] != -1) pre_order_helper(result, left[root]);
    if (right[root] != -1) pre_order_helper(result, right[root]);
  }

  vector <int> post_order() {
    vector<int> result;
    post_order_helper(result, 0);
    return result;
  }

  void post_order_helper(vector<int>& result, int root) {
    if (root == -1) return;
    if (left[root] != -1) post_order_helper(result, left[root]);
    if (right[root] != -1) post_order_helper(result, right[root]);
    result.push_back(key[root]);
  }
};

void print(vector <int> a) {
  for (size_t i = 0; i < a.size(); i++) {
    if (i > 0) {
      cout << ' ';
    }
    cout << a[i];
  }
  cout << '\n';
}

int main() {
  ios_base::sync_with_stdio(0);
  TreeOrders t;
  t.read();
  print(t.in_order());
  print(t.pre_order());
  print(t.post_order());
  return 0;
}
