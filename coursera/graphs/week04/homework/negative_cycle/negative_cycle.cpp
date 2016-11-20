#include <iostream>
#include <vector>
#include <limits>
#include <queue>

using std::vector;
using std::queue;

int negative_cycle(vector<vector<int> > &adj, vector<vector<int> > &cost) {
  if (adj.size() == 0) return 0; 

  vector<int> roots(adj.size(), -1);
  for (int u = 0; u < adj.size(); u++) {
    if (roots[u] != -1) continue;
    roots[u] = u;
    queue<int> rq;
    rq.push(u);
    while(rq.empty() == false) {
      int t = rq.front();
      rq.pop();
      vector<int>& tmp = adj[t];
      for(auto ele: tmp) {
        if(roots[ele] != u) {
          roots[ele] = u;
          rq.push(ele);
        }
      }
    }
  }
  // for(int idx = 0; idx < roots.size(); idx++) std::cout << "idx:" << idx << ", root:" << roots[idx] << std::endl;

  vector<int> dist(adj.size(), std::numeric_limits<int>::max());
  vector<int> prev(adj.size(), -1);
  for (int idx = 0; idx < adj.size(); idx++) {
    if (idx != roots[idx]) continue;
    dist[idx] = 0; // use idx as S, run bellman-ford algorithm

    for(int i = 1; i < adj.size(); i++) {
      if(roots[i] != idx) continue; // reduce complexity
      for(int u = 0; u < adj.size(); u++) {
        if (roots[u] != idx) continue;
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

    for(int u = 0; u < adj.size(); u++) {
      if (roots[u] != idx) continue;
      vector<int>& tmp = adj[u];
      for (int k = 0; k < tmp.size(); k++) {
        int v = tmp[k];
        // std::cout << "round " << adj.size() << ", u " << u << ", dist[u]:" << dist[u] << ", v:" << v << ", dist[v]:" << dist[v] << ", cost:" << cost[u][k] << std::endl;
        if (dist[v] > dist[u] + cost[u][k]) return 1;
      }
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
