#include <iostream>
#include <vector>
#include <map>


using namespace std;

struct Edge {
    int from;
    int to;
};

bool operator<(const Edge& a, const Edge& b) {
    if (a.from < b.from) return true;
    if (a.from > b.from) return false;
    return a.to < b.to;
}

struct ConvertHampathToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertHampathToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        map<Edge, bool> tempEdgeMap;

        for(vector<Edge>::const_iterator item = edges.begin(); item != edges.end(); item++) {
            int from = item->from, to = item->to;
            if (from > to) swap(from, to);
            tempEdgeMap[Edge{from,to}] = true; // starts with zero
        }
        vector<Edge> newEdges;
        newEdges.reserve(tempEdgeMap.size());
        vector<vector<int> > v2e_out(numVertices, vector<int>());
        vector<vector<int> > v2e_in(numVertices, vector<int>());
        for(auto &item : tempEdgeMap) {
            int from = item.first.from;
            int to = item.first.to;
            newEdges.push_back(Edge{from,to});
            v2e_out[from-1].push_back(newEdges.size());
            v2e_in[to-1].push_back(newEdges.size());
            newEdges.push_back(Edge{to,from});
            v2e_out[to-1].push_back(newEdges.size());
            v2e_in[from-1].push_back(newEdges.size());
        }

        edges.swap(newEdges); // update uni-directional edges to var edges

        // generate formulas
        vector<vector<int> > formulas;
        for(int i = 0; i < edges.size(); i+=2) formulas.push_back(vector<int>{-i-1, -i-2}); // (not e_ij) OR (not e_ji) must be true, because one bi-directional edge can only be used ZERO or once
        for(int i = 0; i < numVertices; i++) {
            auto v = v2e_out[i];
            v.insert(v.end(), v2e_in[i].begin(), v2e_in[i].end());
            formulas.push_back(v);
            if (v.size() >= 3) {  // any three edges, e1, e2, e3, must satisfy "not (e1 and e2 and e3)"
                for(int j = 0; j < v.size()-2; j++) {
                    for(int k = j+1; k < v.size()-1; k++) {
                        for(int r = k+1; r < v.size(); r++) {
                            formulas.push_back(vector<int>{-v[j], -v[k], -v[r]});
                        }
                    }
                }
            }
        }

        cout << formulas.size() << " " << edges.size() << endl;
        for(vector<vector<int> >::const_iterator vec = formulas.begin(); vec != formulas.end(); vec++) {
            for(auto &item : *vec) cout << item << " ";
            cout << 0 << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertHampathToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
