#include <iostream>
#include <vector>
#include <utility>

using std::vector;
using std::pair;

struct Node {
    size_t edgeID, prev;
};

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
int bfs(FlowGraph& graph, vector<size_t>& paths, int to) {
    int flow = 0;
    vector<Node> nodes;
    vector<bool> visited(graph.size(), false);
    const vector<size_t> edgeIDs = graph.get_ids(0);
    visited[0] = true;
    for(vector<size_t>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
        const Edge& ed = graph.get_edge(*it);
        if (ed.capacity == 0) continue;
        nodes.push_back(Node{*it, 0})
        if (ed.to == to) {
            paths.push_back(*it); // already included edgeIDs
            flow = ed.capacity;
            break;
        }
    }
    if (flow > 0) {
        return flow;
    }

    size_t nodeSize = nodes.size();
    size_t idx = 0;
    while(idx < nodeSize){
        const Node& node = nodes[idx];
        const Edge& ed = graph.get_edge(node.edgeID);
        if (visited[ed.to] == true) continue; // already visited, skip
        visited[ed.to] = true;
        const vector<size_t> edgeIDs = graph.get_ids(ed.to);
        for(vector<size_it>::const_iterator it = edgeIDs.begin(); it != edgeIDs.end(); it++) {
            const Edge& nextEd = graph.get_edge(*it);
            if (nextEd.capacity == 0) continue; // zero capacity, skip
            nodes.push_back(Node{*it, idx});
            if (nextEd.to == to) {
                flow = nextEd.capacity;
                break;
            }
        }
        if (flow > 0) break;
        idx++;
        nodeSize = nodes.size();
    }
    if (flow == 0) return flow;
    idx = nodes.size()-1;
    while(true){
        const Node& node = nodes[idx];
        size_t edgeID = node.edgeID;
        paths.push_back(edgeID);
        const Edge& ed = graph.get_edge(node.edgeID);
        if (flow == 0) flow = ed.capacity;
        else if (flow > ed.capacity) flow = ed.capacity;
        if (idx==node.prev) break;
        idx = node.prev;
    }
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
