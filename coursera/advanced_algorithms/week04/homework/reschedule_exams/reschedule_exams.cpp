#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <algorithm>
using namespace std;

void removeColor(string& availableColors, char c) {
    string res;
    for(auto item : availableColors) {
        if (c!= item) res.push_back(item);
    }
    availableColors.swap(res);
}

bool propagateColoring(const vector<vector<int> >& graph, vector<string>& availableColors, string& recoloring, int v, char color) {
    if (recoloring[v] > 0) return true;

    recoloring[v] = color;
    removeColor(availableColors[v], color);
    for(auto u : graph[v]) {
        if (recoloring[u] > 0) continue;
        auto& vec = availableColors[u];
        removeColor(vec, color);
        cout << "propagateColoring v=" << v << ", recoloring=" << recoloring << ", availablecolors=" << availableColors[v] << ", u=" << u << ", available colors=" << availableColors[u] << endl;
        if (vec.size() == 0 ) {
            return false;
        } else if (vec.size() == 1) {
            if (propagateColoring(graph, availableColors, recoloring, u, vec[0]) == false) return false;
        }
    }
    return true;
}

bool dfs(const vector<vector<int> >& graph, vector<string>& availableColors, string& recoloring, int v) {
    if (recoloring[v] > 0) return true;
    if (availableColors[v].size() == 0) return false;

    // make a copy of coloring states, in case no color solutions can be found
    string bakRecoloring = recoloring;
    vector<string> bakAvailableColors = availableColors;


    for(auto c : availableColors[v]) {
        cout << "v=" << v << ", recoloring=" << recoloring << ", available=" << availableColors[v] << ", c=" << c << endl;
        if (propagateColoring(graph, availableColors, recoloring, v, c) == false) {
            recoloring = bakRecoloring;
            availableColors = bakAvailableColors;
            continue;
        }
        cout << "after propagate, v=" << v << endl;
        bool allTrue = true;
        for(auto u : graph[v]) {
            if (dfs(graph, availableColors, recoloring, u) == false) {
                allTrue = false;
                break;
            }
        }
        if (allTrue) {
            return true;
        } else {
            recoloring = bakRecoloring;
            availableColors = bakAvailableColors;
        }
    }

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
    vector<vector<int> > graph(n, vector<int>());
    for(const auto& e: edges){
        graph[e.first-1].push_back(e.second-1);
        graph[e.second-1].push_back(e.first-1);
    }

    // update available color table
    vector<string> availableColors(n, "RGB");
    for(int i = 0; i < n; i++) removeColor(availableColors[i], colors[i]);
    string recoloring(n, 0);

    for(int i = 0; i < n; i++) {
        if (dfs(graph, availableColors, recoloring, i) == false) {
            return "";
        }
    }
    return recoloring;
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
