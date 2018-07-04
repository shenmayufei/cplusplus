#include <ios>
#include <iostream>
#include <vector>

using namespace std;

struct Edge {
    int from;
    int to;
};

struct ConvertGSMNetworkProblemToSat {
    int numVertices;
    vector<Edge> edges;

    ConvertGSMNetworkProblemToSat(int n, int m) :
        numVertices(n),
        edges(m)
    {  }

    void printEquisatisfiableSatFormula() {
        int numVar = numVertices * 3;
        vector<vector<int> > formulas;
        for(int i = 0; i < numVertices; i++) {
            formulas.push_back(vector<int>{3*i+1, 3*i+2, 3*i+3});
        }
        for(vector<Edge>::const_iterator it = edges.begin(); it < edges.end(); it++) {
            int from = it->from - 1;
            int to = it->to - 1;
            formulas.push_back(vector<int>{-(from * 3 + 1), -(to * 3 + 1)});
            formulas.push_back(vector<int>{-(from * 3 + 2), -(to * 3 + 2)});
            formulas.push_back(vector<int>{-(from * 3 + 3), -(to * 3 + 3)});
        }

        cout << formulas.size() << " " << numVar << endl;
        for(auto item : formulas){
            for(auto val : item) cout << val << " ";
            cout << 0 << endl;
        }
    }
};

int main() {
    ios::sync_with_stdio(false);

    int n, m;
    cin >> n >> m;
    ConvertGSMNetworkProblemToSat converter(n, m);
    for (int i = 0; i < m; ++i) {
        cin >> converter.edges[i].from >> converter.edges[i].to;
    }

    converter.printEquisatisfiableSatFormula();

    return 0;
}
