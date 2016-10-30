#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;

int isBipartiteNode(vector<vector<int> > &adj, vector<int>& colors, int s) {
  if (colors[1] != -1) return 1;

  colors[s] = 0;
  queue<int> q;
  q.push(s);

  while(q.empty() == false) {
    int node = q.front();
    q.pop();

    int newColor = !colors[node];
    vector<int>& vec = adj[node];
    for(vector<int>::const_iterator it = vec.begin(); it != vec.end(); it++) {
      if (colors[*it] != -1) {
        if (colors[*it] != newColor) return 0; 
      } else {
        colors[*it] = newColor;
        q.push(*it);
      }
    }
  }
  return 1;
}

int bipartite(vector<vector<int> > &adj) {
  vector<int> colors(adj.size(), -1);
  for (int i = 0; i < adj.size(); i++) {
    if( isBipartiteNode(adj, colors, i) == 0) return 0;
  }
  return 1;
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
  std::cout << bipartite(adj);
}
