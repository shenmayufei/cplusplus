#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <chrono>
#include <string>

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
		// generate formulas
		vector<vector<int>> formulas;
	
		// add filter one: for any j, only one of `m[0][j], m[1][j], ..., m[n-1][j]` is true
		// condition count: n * (n-1) / 2 + 1 
		for(int j = 0; j < numVertices; j++) {
			vector<int> conds;
			conds.reserve(numVertices);
			for(int i = 0; i < numVertices; i++) conds.push_back(i * numVertices + j + 1);
			formulas.push_back(conds);

			// any two of them cannot be both true
			for(int k = 0; k < numVertices -1; k++) {
				for(int kk = k+1; kk < numVertices; kk++) 
					formulas.push_back(vector<int>{-conds[k], -conds[kk]});
			}
		}
		// add filter two: for any i, only one of `m[i][0], m[i][1], ..., m[i][n-1]` is true
		// condition count: n * (n-1) / 2 + 1 
		for(int i = 0; i < numVertices; i++) {
			vector<int> conds;
			conds.reserve(numVertices);
			for(int j = 0; j < numVertices; j++) conds.push_back(i * numVertices + j + 1);
			formulas.push_back(conds);

			// any two of them cannot be both true
			for(int k = 0; k < numVertices -1; k++) {
				for(int kk = k+1; kk < numVertices; kk++) 
					formulas.push_back(vector<int>{-conds[k], -conds[kk]});
			}
		}

		// add filter three: how edge and m[i][j] are related?  
   		// if vertex u and v are not connected, then for any j, at most one of (m[u][j], m[v][j+1]) can be true, so are (m[v][j], m[u][j+1])
		// condition count: (n*(n-1)/2 - |E|) * (n-1) * 2
		bool connected[numVertices][numVertices] = {false};
		for(auto &e : edges) {
			connected[e.from-1][e.to-1] = true;
			connected[e.to-1][e.from-1] = true;
		}

		for(int i = 0; i < numVertices-1; i++) {
			for(int j = i+1; j<numVertices; j++) {
				if (connected[i][j]) continue;
				for (int k = 0; k < numVertices-1; k++) {
					formulas.push_back(vector<int>{-(i*numVertices + k + 1), -(j*numVertices + k + 2)});
					formulas.push_back(vector<int>{-(j*numVertices + k + 1), -(i*numVertices + k + 2)});
				}
			}
		}


		// auto t1 = chrono::steady_clock::now();
		// cout << "t3 - t2 = " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() << " micro seconds" << endl;
		cout << formulas.size() << " " << numVertices* numVertices << endl;
		for (auto &vec : formulas) {
			for (auto &item : vec) cout << item << " ";
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
