#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int distance(vector<vector<int> > &adj, int s, int t) {
  vector<int> depth(adj.size(), -1);
  queue<int> q;
  
  depth[s] = 0;
  q.push(s);

  while(q.empty() == false) {
    int item = q.front();
    if (item == t) return depth[item];
    q.pop();
    
    int newDepth = depth[item] + 1;
    vector<int>& vec = adj[item];
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
      if (depth[*it] != -1) continue;
      depth[*it] = newDepth;
      q.push(*it);
    }
  }
  return -1;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y;
    std::cin >> x >> y;
    adj[x - 1].push_back(y - 1);
    adj[y - 1].push_back(x - 1);
  }
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, s, t);
}
