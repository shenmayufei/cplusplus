#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

struct comp {
    comp(vector<vector<int> >* graph) { this->graph = graph; }

    bool operator() (const int i, const int j){
        return (*graph)[i].size() > (*graph)[j].size(); 
    }

    vector<vector<int> >* graph;
};

bool dfs(const vector<vector<int> >& graph, vector<int>& recoloring, vector<vector<bool> >& colorUsage, int v) {
    if (recoloring[v] >= 0) return true;

    // make a copy of coloring states, in case no color solutions can be found
    vector<int> bakRecoloring = recoloring;
    vector<vector<bool> > bakColorUsage = colorUsage;

    // update node v's available coloring options, according to it's connected nodes' colors
    vector<bool> colorUsed = colorUsage[v];
    vector<int> unUsedColors;
    for(int i = 0; i < 3; i++) {
        if (!colorUsed[i]) unUsedColors.push_back(i);
    }
    
    // cannot find an available color for node v
    if (unUsedColors.size() == 0) return false;

    // try un-used colors one by one
    for(auto c : unUsedColors) {
        recoloring[v] = c;
        colorUsage[v][c] = true;
        for(auto u : graph[v]) colorUsage[u][c] = true;
        bool allTrue = true;
        for(auto u : graph[v]) {
            if (false == dfs(graph, recoloring, colorUsage, u)) {  // if any of the next node cannot be colored, try next solution
                allTrue = false;
                break;
            }
        }

        // all next nodes are colored successfully
        if (allTrue) {
            return true; 
        } else {  // recover the color usage
            colorUsage[v][c] = false;
            for(auto u : graph[v]) colorUsage[u][c] = false; 
        } 
    }

    // recover coloring states when the solution doesn't work
    recoloring = bakRecoloring;
    colorUsage = bakColorUsage;
    return false;
}

/*
  Arguments:
    * `n` - the number of vertices.
    * `edges` - list of edges, each edge is a pair (u, v), 1 <= u, v <= n.
    * `colors` - string consisting of `n` characters, each belonging to the set {'R', 'G', 'B'}.
  Return value:
    * If there exists a proper recoloring, return value is a string containing new colors, similar to the `colors` argument.
    * Otherwise, return value is an empty string.
*/
string assign_new_colors(int n, vector<pair<int, int>> edges, string colors) {
    map<char, int> colorMap;
    colorMap['R'] = 0;
    colorMap['G'] = 1;
    colorMap['B'] = 2;
    vector<vector<bool> > colorUsage(n, vector<bool>(3, false));
    vector<vector<int> > graph(n, vector<int>());
    for(const auto& e: edges){
        graph[e.first-1].push_back(e.second-1);
        graph[e.second-1].push_back(e.first-1);
    }

    auto cmp = comp(&graph);
    for(auto& out : graph) {
        sort(out.begin(), out.end(), cmp);
    }
    vector<int> idxs(n, 0);
    for(int i = 0; i < n; i++) idxs[i] = i;
    sort(idxs.begin(), idxs.end(), cmp);

    for(size_t i = 0; i < n; i++) colorUsage[i][colorMap[colors[i]]] = true;
    vector<int> recoloring(n, -1);
    
    string result;
    for(auto idx : idxs) if (false == dfs(graph, recoloring, colorUsage, idx)) return "";
    for(int i = 0; i < n; i++) result.push_back("RGB"[recoloring[i]]);
    return result;
}

int main() {
    int n, m;
    cin >> n >> m;
    string colors;
    cin >> colors;
    vector<pair<int, int> > edges;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back(make_pair(u, v));
    }
    string new_colors = assign_new_colors(n, edges, colors);
    if (new_colors.empty()) {
        cout << "Impossible";
    } else {
        cout << new_colors << endl;
    }
}
