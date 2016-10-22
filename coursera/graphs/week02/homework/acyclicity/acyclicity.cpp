#include <iostream>
#include <vector>

using std::vector;
using std::pair;

bool acyclic_helper(vector<vector<int> >& adj, int v, int key, vector<bool>& visited) {
  if (visited[v]) {
    if (key == v) return true;
    else return false;
  } else {
    visited[v] = true;
    if (key == v) return true; 
  }

  vector<int>& vec = adj[v];
  for(int i = 0; i < vec.size(); i++) {
    if (acyclic_helper(adj, i, key, visited)) return true;
  }
  return false;
}

bool acyclic(vector<vector<int> > &adj) {
  int vNum = adj.size();
  for(int i = 0; i < vNum; i++) {
    vector<bool> visited(adj.size(), false);
    vector<int>& vec = adj[i];
    for(int j = 0; j < vec.size(); j++) {
      if (i == j) continue; // skip checking self
      if (acyclic_helper(adj, j, i, visited)) return true;
    }
  }
  return false;
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
  std::cout << acyclic(adj);
}
