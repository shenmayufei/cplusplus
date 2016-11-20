#include <iostream>
#include <vector>
#include <limits>

using std::vector;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  if (adj.size() == 0) return 0; 

  vector<int> dist(adj.size(), std::numeric_limits<int>::max());
  vector<int> prev(adj.size(), -1);
  dist[0] = 0;  // use the first vertex as S
  for(int i = 0; i < dist.size()-1; i++) {
    for(int u = 0; u < adj.size();u++) {
      if (dist[u] == std::numeric_limits<int>::max()) continue;
      vector<int>& tmp = adj[u];
      for (int k = 0; k < tmp.size(); k++) {
        int v = tmp[k];
        // std::cout << "round " << i+1 << ", u " << u << ", dist[u]:" << dist[u] << ", v:" << v << ", dist[v]:" << dist[v] << ", cost:" << cost[u][k] << std::endl;
        if (dist[v] > dist[u] + cost[u][k])  {
          dist[v] = dist[u] + cost[u][k];
          prev[v] = u;
        }
        // std::cout << "round " << i+1 << ", u " << u << ", dist[u]:" << dist[u] << ", v:" << v << ", dist[v]:" << dist[v] << ", cost:" << cost[u][k] << std::endl << std::endl;
      }
    }
  }

  for(int u = 0; u < adj.size();u++) {
    if (dist[u] == std::numeric_limits<int>::max()) continue;
    vector<int>& tmp = adj[u];
    for (int k = 0; k < tmp.size(); k++) {
      int v = tmp[k];
      // std::cout << "round " << adj.size() << ", u " << u << ", dist[u]:" << dist[u] << ", v:" << v << ", dist[v]:" << dist[v] << ", cost:" << cost[u][k] << std::endl;
      if (dist[v] > dist[u] + cost[u][k]) return 1;
    }
  }
  return 0;
}

int main() {
  int n, m;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cout << negative_cycle(adj, cost);
}
