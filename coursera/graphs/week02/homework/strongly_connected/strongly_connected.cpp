#include <algorithm>
#include <iostream>
#include <vector>

using std::vector;
using std::pair;

void dfs(vector<vector<int> >& adjr, vector<bool>& visited, vector<int>& orders, int& orderStart, int x) {
  if (visited[x]) return;
  visited[x] = true;

  // number it
  orders[x] = ++orderStart; 
  // traverse all its sub nodes
  vector<int>& vec = adjr[x];
  for(vector<int>::iterator it = vec.begin(); it  < vec.end(); it++) {
    // std::cout << "order:" << orderStart << ", x:" << x  << ", to: " << *it << std::endl;
    dfs(adjr, visited, orders, orderStart, *it);
  }
  // number it again
  orders[x] = ++orderStart;
}

void markAsVisited(vector<vector<int> >& adj, vector<bool>& visited, int x) {
  if (visited[x]) return;
  visited[x] = true;
  vector<int>& vec = adj[x];
  for (vector<int>::iterator it = vec.begin(); it != vec.end(); it++) {
    markAsVisited(adj, visited, *it);
  }
}

int number_of_strongly_connected_components(vector<vector<int> > adj) {
  int vNum = adj.size();
  // get the reverse of adj
  vector<vector<int> > adjr(adj.size(), vector<int>());
  for(int i = 0; i < vNum ; i++){
    vector<int>& vec = adj[i];
    for(int j = 0; j < vec.size(); j++) {
      adjr[vec[j]].push_back(i);
    }
  }
  // number every vertex
  vector<int> orders(vNum, 0);
  int currentNumber = 0;
  vector<bool> visited(vNum, false);
  for(int i = 0; i < adjr.size(); i++) {
    dfs(adjr, visited, orders, currentNumber, i);
  }

  // print the final traversal order
  // for (int i = 0; i < vNum; i++) {
  //   std::cout << "i:" << i << ", order:" << orders[i] << std::endl;
  // }

  // sort index by order value
  for(int i = 0; i < vNum; i++) visited[i] = false;
  vector<int> order2idx(vNum*2, -1);
  for(int i = 0; i < vNum; i++) order2idx[orders[i]-1] = i;
  // for(int i = 0; i < order2idx.size(); i++) std::cout << "order:" << i << ", idx:" << order2idx[i] << std::endl;

  int result = 0;
  for(int i = order2idx.size()-1; i >= 0; i--) {
    if(order2idx[i] == -1) continue;
    int idx = order2idx[i];
    if (visited[idx]) continue;
    result++; 
    markAsVisited(adj, visited, idx); // cover all vertices in the region as visited
  }
  return result;
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
  std::cout << number_of_strongly_connected_components(adj);
}
