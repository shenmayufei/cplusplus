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

	// // trim removes vertices with only ONE edge recursively
	// // if it finds out >=3 vertices with only ONE edge, return false
	// bool trim(const int numVertices, const vector<Edge>& edges, vector<map<int,bool> >& v2e, vector<bool>& vertexDisabled, vector<bool>& edgeDisabled) {
	// 	vector<vector<int> > edgeSizeStats(2, vector<int>()); // calculate how many vertices have only zero/one edge
	// 	for(int i = 0; i < numVertices; i++) {
	// 		vector<int>& vec = v2e[i];
	// 		if (vec.size() < 2) edgeSizeStats[vec.size()].push_back(i);
	// 	}
	// 	if (edgeSizeStats[0].size() > 0) return false;
	// 	if (edgeSizeStats[1].size() > 2) return false;

	// 	int numVertexOfOneEdge = edgeSizeStats[1].size()

	// 	for(const auto vIdx : edgeSizeStats[1]) {
	// 		for(const auto item : v2e[i]) {
	// 			if !trimIdx(item.first, v2e, vertexDisabled, edgeDisabled, edgeSizeStats[1], numVertexOfOneEdge){
	// 				return false;
	// 			}
	// 		}
	// 	}


	// }

	void printEquisatisfiableSatFormula() {
		vector<vector<int> > v2e(numVertices, vector<int>());
		for (int i = 0; i < edges.size(); i++){
			const Edge &e = edges[i];
			v2e[e.from - 1][i] = true;
			v2e[e.to - 1][i] = true;
		}

		vector<vector<int> > edgeSizeStats(2, vector<int>()); // calculate how many vertices have only zero/one edge
		for(int i = 0; i < numVertices; i++) {
			vector<int>& vec = v2e[i];
			if (vec.size() < 2) edgeSizeStats[vec.size()].push_back(i);
		}

		// cout << "abc\n";

		if (edgeSizeStats[0].size() > 0 || edgeSizeStats[1].size() > 2) { // unsatisifiable 
			cout << "2 1" << endl;
			cout << "1 0" << endl;
			cout << "-1 0" << endl;
			return;
		}

		// remove vertices with only one edge (we need hamiltonian cycle, not hamiltonian path)
		// so that every vertex has two edges connected with others
		vector<bool> edgeDisabled(edges.size(), false);
		for(auto vIdx : edgeSizeStats[1]) {
			for(auto eIdx : v2e[vIdx])
				edgeDisabled[eIdx]=true;
		}

		vector<int> realEdges;  // 
		for(int i = 0; i < edges.size(); i++) {
			if (!edgeDisabled[i]) realEdges.push_back(i);
		}
		map<int, int> idxMapping;
		for(int i = 0; i < realEdges.size(); i++) {
			idxMapping[realEdges[i]+1] = i+1;
		}

		// re-construct v2e
		for(auto &vec : v2e) {
			vector<int> tmpVec;
			for(auto eIdx: vec) {
				if (edgeDisabled[eIdx]==false) {
					tmpVec.push_back(idxMapping[eIdx+1]);
				}
			}
			vec.swap(tmpVec);
		}

		// generate formulas
		vector<vector<int>> formulas;

		// add filter: every vertex must have 2 and only two edges used
		for(auto &eVec: v2e) {
			if (eVec.size() == 0) continue;
			if (eVec.size() < 2 ) {
				formulas.push_back(eVec);
				continue;
			}

			// add filter: at least 2 (any n-1 edges chosen)
			for(int offset = 0; offset < eVec.size(); offset++) {
				vector<int> tmpVec(eVec.begin(), eVec.end());
				tmpVec.erase(tmpVec.begin() + offset);
				formulas.push_back(tmpVec);
			}

			// add filter: at most 2 (any 3 edges chosen)
			for(int i = 0; i < eVec.size()-2; i++) {
				for(int j = i+1; j < eVec.size() - 1; j++) {
					for(int k = j+1; k < eVec.size(); k++) {
						formulas.push_back(vector<int>{-eVec[i], -eVec[j], -eVec[k]});
					}
				}
			}
		}

		cout << formulas.size() << " " << realEdges.size() << endl;
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
