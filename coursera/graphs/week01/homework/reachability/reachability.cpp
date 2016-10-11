#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool reach_helper(vector<vector<int> > &adj, vector<bool> &visited, int x, int y) {
  // set x as visited
  visited[x] = true;

  // if x equals y, return true
  if (x == y) return true;

  const vector<int>& vArr = adj[x];
  for(vector<int>::const_iterator it = vArr.begin(); it != vArr.end(); it++) {
    if (visited[*it]) continue;
    if (reach_helper(adj, visited, *it, y)) return true;
  }
  return false;
}

int reach(vector<vector<int> > &adj, int x, int y) {
  vector<bool> visited(adj.size(), false);

  const vector<int>& vArr = adj[x];
  for(vector<int>::const_iterator it = vArr.begin(); it != vArr.end(); it++) {
    if (reach_helper(adj, visited, *it, y)) return 1;
  }

  return 0;
}

int main() {
  size_t n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (size_t i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int x, y;
  std::cin >> x >> y;
  std::cout << reach(adj, x - 1, y - 1);
}
