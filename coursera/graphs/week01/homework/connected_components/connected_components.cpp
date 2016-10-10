#include <iostream>
#include <vector>

using std::vector;
using std::pair;

int dfs(vector<vector<int> >& adj, vector<int>& visited, int idx, int c_number) {
  if (visited[idx] > 0) return 0; // skipped
  visited[idx] = c_number;
  
  int success = 1;
  vector<int>& vArr = adj[idx];
  for(std::vector<int>::const_iterator it = vArr.begin(); it != vArr.end(); it++) {
    if (visited[*it] > 0) continue;
    success += dfs(adj, visited, *it, c_number);
  }
  return success;
}

int number_of_components(vector<vector<int> > &adj) {
  int res = 0;
  //write your code here
  vector<int> visited(adj.size(), 0);
  int c_start = 1;  // start from 1, which is BIGGER than 0
  for(size_t i = 0; i < adj.size(); i++) {
    if (dfs(adj, visited, i, c_start) > 0) c_start++; // only if a new component is established, c_start increases by ONE
  }
  return c_start-1;
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
  std::cout << number_of_components(adj);
}
