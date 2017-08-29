#include <iostream>
#include <vector>
#include <algorithm>
#include <memory>
#include <queue>

using std::vector;
using std::cin;
using std::cout;
using std::queue;

class FlowGraph {
public:
  struct Edge{
    int from, to, capacity;
  };

private:
  // List of all - forward and backward - edges
  vector<Edge> edges;

  // These adjacency lists store only indices of edges in the edges list
  vector<vector<size_t> > graph;

public:
  explicit FlowGraph(size_t n): graph(n) {}

  void add_edge(int from, int to, int capacity){
    Edge forward_edge = {from, to, capacity};
    Edge backward_edge = {to, from, 0};
    graph[from].push_back(edges.size());
    edges.push_back(forward_edge);
    graph[to].push_back(edges.size());
    edges.push_back(backward_edge);
  }

  // vertex number
  size_t size() const {
    return graph.size();
  }

  // edge id list
  const vector<size_t>& get_ids(int from) const {
    return graph[from];
  }

  // get edge by id
  const Edge& get_edge(size_t id) const {
    return edges[id];
  }

  void update_capacity(size_t id, int flow) {
    edges[id].capacity -= flow;
    edges[id ^ 1].capacity += flow;
  }
};

// bfs does a breadth-first search to FlowGraph graph
// from vertex "from", to vertex "to"
bool bfs(FlowGraph& fg, int from, int to) {
  queue<size_t> vIDs;
  vector<bool> visited(fg.size(), false);
  vector<int> parentEdges(fg.size(), -1);
  bool found = false;
  
  vIDs.push(from);
  visited[from] = true;
  while(!vIDs.empty() && !found) {
    size_t vID = vIDs.front();
    vIDs.pop();
    const vector<size_t> edgeIDs = fg.get_ids(vID);
    for(vector<size_t>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
      const FlowGraph::Edge& ed = fg.get_edge(*it);
      if (ed.capacity <= 0 || visited[ed.to]) continue;
      visited[ed.to] = true;
      parentEdges[ed.to] = *it;  // set parentEdges[v] as edge ID which lead to it
      if (ed.to == to) {
        found = true;
        break;
      }
      vIDs.push(ed.to);
    }
  }

  while(parentEdges[to] != -1) {
    size_t eID = parentEdges[to];
    fg.update_capacity(eID, 1);
    to = eID;
  }

  return found;
}

class StockCharts {
 public:
  void Solve() {
    vector<vector<int> > stock_data = ReadData();
    int result = MinCharts(stock_data);
    WriteResponse(result);
  }

 private:
  vector<vector<int> > ReadData() {
    int num_stocks, num_points;
    cin >> num_stocks >> num_points;
    vector<vector<int> > stock_data(num_stocks, vector<int>(num_points));
    for (int i = 0; i < num_stocks; ++i)
      for (int j = 0; j < num_points; ++j) {
        cin >> stock_data[i][j];
      }
    return stock_data;
  }

  void WriteResponse(int result) {
    cout << result << "\n";
  }

  int MinCharts(const vector<vector<int> >& stock_data) {
    // concept:
    // 1. build a DAG (n vertices)
    // 2. build bipartite graph based on the DAG
    // 3. find the maximum flow (residual graph)
    // 4. count the number of edges from Source vertex in residual graph

    // Actually,while coding, we do not need the DAG
    // We could build bipartite graph directly

    size_t stock_count = stock_data.size();
    
    // step 1. construct bipartite graph
    size_t bn = 2 + 2 * stock_count;
    FlowGraph bp(bn);
    for (size_t i = 1; i <= stock_count; i++) bp.add_edge(0, i, 1);
    for (size_t i = stock_count; i < bn-1; i++) bp.add_edge(i, bn-1, 1);
    for(int i = 0; i < stock_count - 1; i++) {
      for(int j = i+1; j < stock_count; j++) {
        if (compare(stock_data[i], stock_data[j])) {
          bp.add_edge(i+1, j+stock_count+1, 1);
        } else if (compare(stock_data[j], stock_data[i])) {
          bp.add_edge(j+1, i+stock_count+1, 1);
        }
      }
    }

    // step 2. get the residual graph (with maximum flow)
    while(bfs(bp, 0, bn-1));

    // step 3. count the number of edges from Source Vertex in residual network
    int result = 0;
    const vector<size_t>& eIDs = bp.get_ids(0);
    for(vector<size_t>::const_iterator it = eIDs.begin(); it < eIDs.end(); it++) {
      const FlowGraph::Edge& ed = bp.get_edge(*it);
      if (ed.capacity > 0) result++;
    }

    return result;
  }

  bool compare(const vector<int>& stock1, const vector<int>& stock2) {
    for (int i = 0; i < stock1.size(); ++i)
      if (stock1[i] >= stock2[i])
        return false;
    return true;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  StockCharts stock_charts;
  stock_charts.Solve();
  return 0;
}
