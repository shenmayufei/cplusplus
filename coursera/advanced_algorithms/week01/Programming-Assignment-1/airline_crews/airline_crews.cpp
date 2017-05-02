#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
#include <memory>
#include <limits>


using std::vector;
using std::cin;
using std::cout;
using std::queue;
using std::numeric_limits;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity;
    };

private:
    /* List of all - forward and backward - edges */
    vector<Edge> edges;

    /* These adjacency lists store only indices of edges in the edges list */
    vector<vector<size_t> > graph;

public:
    explicit FlowGraph(size_t n): graph(n) {}

    void add_edge(int from, int to, int capacity) {
        /* Note that we first append a forward edge and then a backward edge,
         * so all forward edges are stored at even indices (starting from 0),
         * whereas backward edges are stored at odd indices in the list edges */
        Edge forward_edge = {from, to, capacity};
        Edge backward_edge = {to, from, 0};
        graph[from].push_back(edges.size());
        edges.push_back(forward_edge);
        graph[to].push_back(edges.size());
        edges.push_back(backward_edge);
    }

    size_t size() const {
        return graph.size();
    }

    const vector<size_t>& get_ids(int from) const {
        return graph[from];
    }

    const Edge& get_edge(size_t id) const {
        return edges[id];
    }

    void update_capacity(size_t id, int flow) {
        edges[id].capacity -= flow;
        edges[id ^ 1].capacity += flow;
    }
};

// dfs do a breadth-first search to FlowGraph graph, from vertex "from", to vertex
// "to", if found vertext to, return flow
int bfs(FlowGraph& graph, vector<size_t>& paths, int from, int to) {
    queue<size_t> vertexIDs;
    vector<bool> visited(graph.size(), false);
    vector<int> parentEdges(graph.size(), -1);
    vertexIDs.push(from);
    visited[from] = true;
    bool found = false;
    while(!vertexIDs.empty() && !found) {
        size_t vertexID = vertexIDs.front();
        vertexIDs.pop();
        const vector<size_t> edgeIDs = graph.get_ids(vertexID);
        for(vector<size_t>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
            const FlowGraph::Edge& ed = graph.get_edge(*it);
            if (ed.capacity <= 0 || visited[ed.to]) continue;
            visited[ed.to] = true;
            parentEdges[ed.to] = *it;  // set parentEdges[v] as edge ID which lead to it
            if (ed.to == to) {
                found = true;
                break;
            }
            vertexIDs.push(ed.to);
        }
    }

    if (!found) return 0; // cannot find a valid flow
    int flow = numeric_limits<int>::max();
    while(to != from) {
        size_t edgeID = parentEdges[to];
        const FlowGraph::Edge& ed = graph.get_edge(edgeID);
        if (flow > ed.capacity) flow = ed.capacity;
        paths.push_back(edgeID);
        to = ed.from;
        // std::cout << "from:" << from << ", to:" << to << ", edge:" << edgeID << ", edge.from:" << ed.from << ", edge.to:"<<ed.to <<  std::endl;
    }
    
    return flow;
}

class MaxMatching {
 public:
  void Solve() {
    vector<vector<bool> > adj_matrix = ReadData();
    vector<int> matching = FindMatching(adj_matrix);
    WriteResponse(matching);
  }

 private:
  vector<vector<bool> > ReadData() {
    int num_left, num_right;
    cin >> num_left >> num_right;
    vector<vector<bool> > adj_matrix(num_left, vector<bool>(num_right));
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j) {
        int bit;
        cin >> bit;
        adj_matrix[i][j] = (bit == 1);
      }
    return adj_matrix;
  }

  void WriteResponse(const vector<int>& matching) {
    for (int i = 0; i < matching.size(); ++i) {
      if (i > 0)
        cout << " ";
      if (matching[i] == -1)
        cout << "-1";
      else
        cout << (matching[i] + 1);
    }
    cout << "\n";
  }

  vector<int> FindMatching(const vector<vector<bool> >& adj_matrix) {
    // Replace this code with an algorithm that finds the maximum
    // matching correctly in all cases.
    int num_left = adj_matrix.size();
    int num_right = adj_matrix[0].size();

    // build the Graph
    int vertexNum = 2 + num_left + num_right;
    FlowGraph graph(vertexNum);
    for (int i = 0; i < num_left; ++i) graph.add_edge(0, i+1, 1);
    for (int i = 0; i < num_left; ++i)
      for (int j = 0; j < num_right; ++j)
        if (adj_matrix[i][j]) {
          graph.add_edge(i+1, num_left+j+1, 1);
        }
    for (int j = 0; j < num_right; ++j) 
      graph.add_edge(j+num_left+1, vertexNum - 1, 1);

    // find the max flow Graph^f
    while(true){
        vector<size_t> paths;
        int thisFlow = bfs(graph, paths, 0, graph.size() -1);
        if (thisFlow == 0) break;
        for(vector<size_t>::const_iterator it = paths.begin(); it != paths.end(); it++) {
            graph.update_capacity(*it, thisFlow);
        }
    }

    // find the matching according to the max flow Graph^f
    // find all flows from vertex [num_left+1, num_left+num_right] to 
    // vertex [1,num_left]
    vector<int> matching(num_left, -1);
    for(size_t v = num_left+1; v <= num_left+num_right; v++) {
      const vector<size_t>& edgeIDs = graph.get_ids(v);
      for(vector<size_t>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
        const FlowGraph::Edge& ed = graph.get_edge(*it);
        if (ed.to >= 1 && ed.to <= num_left && ed.capacity>0) matching[ed.to-1] = v - num_left - 1;
      }
    }
    
    return matching;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  MaxMatching max_matching;
  max_matching.Solve();
  return 0;
}
