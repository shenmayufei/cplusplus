#include <bits/stdc++.h>
using namespace std;

struct Clause {
    int firstVar;
    int secondVar;
};

// getGraphIndex returns corresponding index of val in graph
// (1, false) => 0
// (1, true) => 1
// (2, false) => 2
// (2, true) => 3
// (n, false) => n * 2 - 2
// (n, true) => n * 2 - 1
// (-1, false) => 1
// (-1, true) => 0
// (-n, false) => n * 2 - 1
// (-n, true) => n * 2 - 2
int getGraphIndex(int val, bool negate) {
    if (negate) val = - val;
    if (val > 0) return val * 2 - 2;
    else return -val * 2 - 1;
}

void postOrderDFSHelper(const vector<vector<int> >& g, int v, vector<bool>& visited, vector<int>& polist) {
    if (visited[v]) return;
    visited[v] = true;
    for(const auto u : g[v]) {
        postOrderDFSHelper(g, u, visited, polist);
    }
    // cout << "v = " << v << endl;
    polist.push_back(v);
}

// postOrder calculates a post order list of graph g
vector<int> postOrder(const vector<vector<int> >& g) {
    int numVertices = g.size();
    vector<int> polist;
    polist.reserve(numVertices);
    vector<bool> visited(numVertices, false);
    for(int v = 0; v < numVertices; v++) {
        postOrderDFSHelper(g, v, visited, polist);
    }
    return polist;
}

void setSccDFSHelper(const vector<vector<int> >& g, int v, int root, vector<bool>& visited, vector<int>& scc) {
    if (visited[v]) return;
    visited[v] = true;
    scc[v] = root;
    for(const auto u: g[v]) {
        setSccDFSHelper(g, u, root, visited, scc);
    }
}


struct TwoSatisfiability {
    int numVars;
    vector<Clause> clauses;

    TwoSatisfiability(int n, int m) :
        numVars(n),
        clauses(m)
    {  }

    bool isSatisfiable(vector<int>& result) {
        vector<vector<int> > graph(numVars * 2, vector<int>());  // postive first, negative second
        for(const auto& c : clauses) {
            // cout << "c = (" << c.firstVar << ", " << c.secondVar << ")"  << endl;
            graph[getGraphIndex(c.firstVar, true)].push_back(getGraphIndex(c.secondVar, false));
            graph[getGraphIndex(c.secondVar, true)].push_back(getGraphIndex(c.firstVar, false));
        }

        // get reverse graph
        vector<vector<int> > graphR(numVars * 2, vector<int>()); // reverse of graph
        for(int u = 0; u < numVars * 2; u++) {
            for(auto v : graph[u]) {
                graphR[v].push_back(u);
            }
        }

        vector<int> postOrderList = postOrder(graphR);
        reverse(postOrderList.begin(), postOrderList.end()); // reverse post order
        vector<bool> visited(numVars* 2, false);
        vector<int> scc(numVars * 2, 0);
        for(auto v : postOrderList) {
            setSccDFSHelper(graph, v, v, visited, scc);
        }
        bool satisfiable = true;
        for(int i = 0; i < numVars*2; i+=2) {
            if (scc[i] == scc[i+1]) {
                satisfiable = false;
                break;
            }
        }
        // not satisfiable
        if (!satisfiable) {
            return false;
        }

        // satisfiable
        vector<bool> alreadySet(numVars, false);
        for(auto v : postOrderList) {
            int originV = v / 2;
            bool isNeg = v - originV * 2 == 1;
            if (alreadySet[originV]) continue;
            result[originV] = isNeg;
            alreadySet[originV] = true;
        }
        return true;
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    TwoSatisfiability twoSat(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> twoSat.clauses[i].firstVar >> twoSat.clauses[i].secondVar;
    }

    vector<int> result(n);
    if (twoSat.isSatisfiable(result)) {
        cout << "SATISFIABLE" << endl;
        for (int i = 1; i <= n; ++i) {
            if (result[i-1]) {
                cout << -i;
            } else {
                cout << i;
            }
            if (i < n) {
                cout << " ";
            } else {
                cout << endl;
            }
        }
    } else {
        cout << "UNSATISFIABLE" << endl;
    }

    return 0;
}
