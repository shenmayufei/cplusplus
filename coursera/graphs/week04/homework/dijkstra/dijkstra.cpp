#include <iostream>
#include <vector>
#include <queue>

using std::vector;
using std::queue;
using std::pair;
using std::priority_queue;

typedef pair<int, int> IntPair;
class Greater
{
public:
  bool operator() (const IntPair& lhs, const IntPair& rhs) const
  {
    return lhs.second > rhs.second;
  }
};

int distance(vector<vector<int> > &adj, vector<vector<int> > &cost, int s, int t) {
  if (s == t) return t;

  vector<int> dist(adj.size(), -1); // initialize dist
  dist[s] = 0; 

  priority_queue<IntPair> q; // store known distances
  q.push(std::make_pair(s, dist[s]));

  while(q.empty() == false) {
    int idx = q.top().first;
    // std::cout << "idx: " << idx << ", val: " << dist[idx] << std::endl;
    q.pop();
    vector<int>& vertices = adj[idx];
    vector<int>& edges = cost[idx];
    for(int i = 0; i < vertices.size() ; i++) {
      int v = vertices[i];
      int e = edges[i];
      if (dist[v] < 0 || dist[v] > dist[idx] + e) {
        dist[v] = dist[idx] + e;
        q.push(std::make_pair(v, dist[v]));
      }
    }
  }

  return dist[t];
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
  int s, t;
  std::cin >> s >> t;
  s--, t--;
  std::cout << distance(adj, cost, s, t);
}
