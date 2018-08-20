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
    else return val * 2 - 1;
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
            graph[getGraphIndex(c.firstVar, true)].push_back(getGraphIndex(c.secondVar, false));
            graph[getGraphIndex(c.secondVar, true)].push_back(getGraphIndex(c.firstVar, false));
        }
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
