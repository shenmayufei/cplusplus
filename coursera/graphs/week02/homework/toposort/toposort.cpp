#include <iostream>
#include <algorithm>
#include <vector>

using std::vector;
using std::swap;
using std::pair;

void dfs(vector<vector<int> > &adj, vector<bool> &used, vector<int>& order, int x) {
  if (used[x]) return;

  vector<int>& vec = adj[x];
  bool isSink = true;
  for(vector<int>::iterator it = vec.begin(); it != vec.end() ; it++){
    if (used[*it]) continue;
    dfs(adj, used, order, *it);  // dfs next vertex
    if (used[*it] == false) isSink = false; // if after dfs , next vertex still not used, it's also set as not used
  }
  if (isSink) {
    used[x] = 1;
    order.push_back(x);
  }
}

vector<int> toposort(vector<vector<int> > adj) {
  vector<bool> used(adj.size(), false);
  vector<int> order;
  for(int i = 0; i < adj.size(); i++) {
    dfs(adj, used, order, i);
  }
  size_t whole = order.size();
  size_t half = whole/2;
  for(size_t i = 0; i < half; i++) {
    swap(order[i], order[whole-1-i]);
  }
  return order;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
  }
  vector<int> order = toposort(adj);
  for (size_t i = 0; i < order.size(); i++) {
    std::cout << order[i] + 1 << " ";
  }
}
