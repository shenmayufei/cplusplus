#include <iostream>
#include <vector>
#include <queue>
#include <limits>
#include <algorithm>

using std::vector;
using std::queue;
using std::numeric_limits;

/* This class implements a bit unusual scheme for storing edges of the graph,
 * in order to retrieve the backward edge for a given edge quickly. */
class FlowGraph {
public:
    struct Edge {
        int from, to, capacity, flow;
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
        Edge forward_edge = {from, to, capacity, 0};
        Edge backward_edge = {to, from, 0, 0};
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

    void add_flow(size_t id, int flow) {
        /* To get a backward edge for a true forward edge (i.e id is even), we should get id + 1
         * due to the described above scheme. On the other hand, when we have to get a "backward"
         * edge for a backward edge (i.e. get a forward edge for backward - id is odd), id - 1
         * should be taken.
         *
         * It turns out that id ^ 1 works for both cases. Think this through! */
        edges[id].flow += flow;
        edges[id ^ 1].flow -= flow;
    }
};

FlowGraph read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    FlowGraph graph(vertex_count);
    for (int i = 0; i < edge_count; ++i) {
        int u, v, capacity;
        std::cin >> u >> v >> capacity;
        graph.add_edge(u - 1, v - 1, capacity);
    }
    return graph;
}

// dfs do a breadth-first search to FlowGraph graph, from vertex "from", to vertex
// "to", if found vertext to, return flow
int bfs(FlowGraph& graph, vector<int>& paths, int from, int to) {
    queue<size_t> vertexIDs;
    vector<bool> visited(graph.size(), false);
    vector<int> parentEdges(graph.size(), -1);
    vertexIDs.push(from);
    bool found = false;
    while(!vertexIDs.empty() && !found) {
        size_t vertexID = vertextIDs.front();
        vertexIDs.pop();
        visited[vertexID] = true;
        const vector<size_t> edgeIDs = graph.get_ids(vertexID);
        for(vector<size_t>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
            const Edge& ed = graph.get_edge(*it);
            if (ed.capacity == 0) continue;
            parentEdges[ed.to] = *it;  // set parentEdges[v] as edge ID which lead to it
            if (ed.to == to) {
                found = true;
                break;
            }
            vertexIDs.push(ed.to);
        }
    }

    if (!found) return 0; // cannot find a valid flow
    int flow = numeric_limit<int>::max();
    while(to != from) {
        size_t edgeID = parentEdges[to];
        const Edge& ed = graph.get_edge(edgeID);
        if (flow > ed.capacity) flow = ed.capacity;
        path.push_back(edgeID);
        to = ed.from;
    }
    
    std::reverse(path.begin(), path.end());
    return flow;
}

int max_flow(FlowGraph& graph, int from, int to) {
    int flow = 0;

    while(true){
        // calculate this flow
        vector<size_t> paths;
        int thisFlow = bfs(graph, paths, to);
        flow+= thisFlow;
        // paths is the edges of path in reversed order, thisFlow is the max flow available
        
        // @todo: add the flow to Graph
    }

    return flow;
}

int main() {
    std::ios_base::sync_with_stdio(false);
    FlowGraph graph = read_data();

    std::cout << max_flow(graph, 0, graph.size() - 1) << "\n";
    return 0;
}
