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

	vector<vector<int> > getCyclesHelper(int pivot, int eID, int vID, const vector<vector<int> >& v2e, vector<bool> edgeVisited, vector<bool> vertexVisited) {
		if (edgeVisited[eID]) return vector<vector<int> >();  // if edge is visited, skip
		if (pivot == vID) return vector<vector<int> >{vector<int>{eID}}; // if the other end of the edge is pivot, we got a cycle
		if (vertexVisited[vID]) return vector<vector<int> >(); // if the other end of the edge is not pivot, and visited, it's already in path, skip
		edgeVisited[eID] = true;
		vertexVisited[vID] = true;

		vector<vector<int> > result;
		for(auto eIdx : v2e[vID]) {
			if (edgeVisited[eIdx]) continue;
			const int vIdx = edges[eIdx].from-1 == vID ? edges[eIdx].to - 1: edges[eIdx].from - 1;
			vector<vector<int> > subResult = getCyclesHelper(pivot, eIdx, vIdx, v2e, edgeVisited, vertexVisited);
			for(auto item : subResult) {
				item.push_back(eID);
				result.push_back(item);
			}
		}
		return result;
	}

	vector<vector<int> > getCycles(int pivot, const vector<vector<int> >& v2e) {
		vector<vector<int> > result;

		vector<bool> vertexVisited(numVertices, false);
		vertexVisited[pivot] = true;
		vector<bool> edgeVisited(edges.size(), false);

		for(auto eID : v2e[pivot]) {
			const int uID = edges[eID].from-1 == pivot? edges[eID].to-1: edges[eID].from-1;

			vector<vector<int> > subResult = getCyclesHelper(pivot, eID, uID, v2e, edgeVisited, vertexVisited);
			result.insert(result.end(), subResult.begin(), subResult.end());
		}

		cout << "pivot = " << pivot  << ", result =" << endl;
		for(int i = 0;i < result.size(); i++) {
			cout << i <<  ". [";
			for (auto it : result[i]) cout << it << ",";
			cout << "]\n";
		}
		return result;
	}

	void printEquisatisfiableSatFormula() {
		auto t1 = chrono::steady_clock::now();
		vector<vector<int> > v2e(numVertices, vector<int>());
		for (int i = 0; i < edges.size(); i++){
			const Edge &e = edges[i];
			v2e[e.from - 1].push_back(i);
			v2e[e.to - 1].push_back(i);
		}

		vector<vector<int> > edgeSizeStats(2, vector<int>()); // calculate how many vertices have only zero/one edge
		for(int i = 0; i < numVertices; i++) {
			vector<int>& vec = v2e[i];
			if (vec.size() < 2) edgeSizeStats[vec.size()].push_back(i);
		}

		if (edgeSizeStats[0].size() > 0 || edgeSizeStats[1].size() > 2) { // unsatisifiable 
			cout << "2 1" << endl;
			cout << "1 0" << endl;
			cout << "-1 0" << endl;
			return;
		}

		// generate formulas
		vector<vector<int>> formulas;

		auto t2 = chrono::steady_clock::now();
		cout << "t2 - t1 = " << chrono::duration_cast<chrono::microseconds>(t2 - t1).count() << " micro seconds" << endl;
		// add filter: all edges in a cycle cannot all be true
		map<vector<int>, bool> cycleMapping;
		for(int i = 0; i < numVertices; i++) {
			vector<vector<int> > cycles = getCycles(i, v2e);
			for(auto &vs : cycles) {
				sort(vs.begin(), vs.end());
				cycleMapping[vs] = true;
			}
			// auto t21 = chrono::steady_clock::now();
			// cout << "vertex " << i << ", t2i - t2 = " << chrono::duration_cast<chrono::microseconds>(t21 - t2).count() << " micro seconds" << endl;
		}
		for(auto &mIt : cycleMapping) {
			vector<int> es = mIt.first;
			for(auto &e : es) {
				e+=1;
				// cout << e << " ";
			}
			// cout << endl;
			formulas.push_back(es);
		}
		// cout << "end " << endl;

		auto t3 = chrono::steady_clock::now();
		cout << "t3 - t2 = " << chrono::duration_cast<chrono::microseconds>(t3 - t2).count() << " micro seconds" << endl;
		// add filter: every vertex must have at least 1 and at most 2 edges used
		for(auto &eVec: v2e) {
			for(auto &e : eVec) e+=1;
			// add filter: at least 1
			formulas.push_back(eVec); 

			if (eVec.size() < 3) continue;

			// add filter: at most 2 (any 3 edges chosen)
			for(int i = 0; i < eVec.size()-2; i++) {
				for(int j = i+1; j < eVec.size() - 1; j++) {
					for(int k = j+1; k < eVec.size(); k++) {
						formulas.push_back(vector<int>{-eVec[i], -eVec[j], -eVec[k]});
					}
				}
			}
		}

		auto t4 = chrono::steady_clock::now();
		cout << "t4 - t3 = " << chrono::duration_cast<chrono::microseconds>(t4 - t3).count() << " micro seconds" << endl;
		cout << formulas.size() << " " << edges.size() << endl;
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
