#include <algorithm>
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <queue>
#include <utility>

using std::pair;
using std::vector;
using std::priority_queue;

typedef pair<int, double> IntPair;
class Greater
{
public:
  bool operator() (const IntPair& lhs, const IntPair& rhs) const
  {
    return lhs.second > rhs.second;
  }
};

double minimum_distance(vector<int> x, vector<int> y) {
  double result = 0.;
  int vSize = x.size();
  if(vSize <= 1) return result;

  vector<double> dist(vSize, -1);
  vector<int> prev(vSize, -1);
  // initialize distances between any two points
  vector< vector<double> > cost(vSize, vector<double>(vSize, 0.0));
  for(int i = 0; i < vSize; i++) {
    for(int j = i+1; j < vSize; j++) {
      cost[i][j] = cost[j][i] = sqrt(pow(x[i] - x[j], 2) + pow(y[i] - y[j], 2));
    }
  }
  // starting from points ZERO, get the shortest path
  vector<bool> visited(vSize, false);
  priority_queue<IntPair, vector<IntPair>, Greater> pq;
  pq.push(std::make_pair(0, 0.0));
  dist[0] = 0.0;
  while(pq.empty() == false) {
    int u = pq.top().first;
    double udist = pq.top().second;
    pq.pop();
    if (visited[u] == true) continue; // if outdated, skip
    result += udist;
    visited[u] = true;
    for(int i = 0; i < vSize; i++) {
      if (i==u || visited[i] == true) continue; // if used, skip
      if (dist[i] == -1 || dist[i] > cost[u][i]) {
        dist[i] = cost[u][i];
        prev[i] = u;
        pq.push(std::make_pair(i, dist[i]));
      }
    }
  }

  // for(int i = 0; i < vSize; i++) std::cout << "i:(" << x[i] << "," << y[i] << "), prev:(" << x[prev[i]] << "," << y[prev[i]] << "), dist:" << dist[i] << std::endl;

  return result;
} 

int main() {
  size_t n;
  std::cin >> n;
  vector<int> x(n), y(n);
  for (size_t i = 0; i < n; i++) {
    std::cin >> x[i] >> y[i];
  }
  std::cout << std::setprecision(10) << minimum_distance(x, y) << std::endl;
}
