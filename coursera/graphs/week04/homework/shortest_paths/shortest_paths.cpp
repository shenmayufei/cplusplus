#include <iostream>
#include <limits>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;

void shortest_paths(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, vector<long long> &dist, vector<bool> &reachable, vector<int> &shortest) {
  dist[s] = 0;
  reachable[s] = true;

  // find all reachable ones, O(V+E)
  queue<int> rq;
  rq.push(s);
  while(rq.empty() == false) {
    int t = rq.front();
    rq.pop();
    vector<int>& tmp = adj[t];
    for(int i = 0; i < tmp.size() ; i++) {
      int ele = tmp[i];
      if (reachable[ele] == false) {
        reachable[ele] = true;
        dist[ele] = dist[t] + cost[t][i];
        rq.push(ele);
      }
    }
  }

  vector<int> prev(adj.size(), -1);
  // run Bellman-Ford algorithm for reachable nodes only
  // O(V*E)
  for(int i = 1; i < dist.size(); i++) {
    if(reachable[i] == false) continue; // reduce complexity
    int changed = 0;
    for(int u = 0; u < adj.size();u++) {
      if (reachable[u] == false) continue;
      vector<int>& tmp = adj[u];
      for (int k = 0; k < tmp.size(); k++) {
        int v = tmp[k];
        if (dist[v] > dist[u] + cost[u][k])  {
          dist[v] = dist[u] + cost[u][k];
          prev[v] = u;        
        }
      }
    }
  }

  for(int u = 0; u < adj.size(); u++) {
    if (reachable[u] == false) continue;
    vector<int>& tmp = adj[u];
    for (int k = 0; k < tmp.size(); k++) {
      int v = tmp[k];
      // std::cout << "round " << adj.size() << ", u " << u << ", dist[u]:" << dist[u] << ", v:" << v << ", dist[v]:" << dist[v] << ", cost:" << cost[u][k] << std::endl;
      if (dist[v] > dist[u] + cost[u][k]) {
        dist[v] = dist[u] + cost[u][k];
        shortest[v] = 0; // there no shortest for those
        prev[v] = u;
      }
    }
  }

  // reverse find negative cycles
  for(int u = 0; u < adj.size(); u++) {
    if (reachable[u] == false) continue;
    if (shortest[u] == 1) continue;
    int v = prev[u];
    while(u != v) {
      shortest[v] = 0;
      v = prev[v];
    }
  }
}

int main() {
  int n, m, s;
  std::cin >> n >> m;
  vector<vector<int> > adj(n, vector<int>());
  vector<vector<int> > cost(n, vector<int>());
  for (int i = 0; i < m; i++) {
    int x, y, w;
    std::cin >> x >> y >> w;
    adj[x - 1].push_back(y - 1);
    cost[x - 1].push_back(w);
  }
  std::cin >> s;
  s--;
  vector<long long> distance(n, std::numeric_limits<long long>::max());
  vector<bool> reachable(n, false);
  vector<int> shortest(n, 1);
  shortest_paths(adj, cost, s, distance, reachable, shortest);
  for (int i = 0; i < n; i++) {
    if (!reachable[i]) {
      std::cout << "*\n";
    } else if (!shortest[i]) {
      std::cout << "-\n";
    } else {
      std::cout << distance[i] << "\n";
    }
  }
}
