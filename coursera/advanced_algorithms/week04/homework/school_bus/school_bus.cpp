#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>
#include <utility>

using std::vector;
using std::unordered_map;
typedef vector<vector<int> > Matrix;

const int INF = 1e9;

Matrix read_data() {
    int vertex_count, edge_count;
    std::cin >> vertex_count >> edge_count;
    Matrix graph(vertex_count, vector<int>(vertex_count, INF));
    for (int i = 0; i < edge_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to >> weight;
        --from, --to;
        graph[from][to] = graph[to][from] = weight;
    }
    return graph;
}

int getLastNodeIdx(int k) {
    return k >> 20;
}
int getNodesIdx(int k) {
    return k & ((1 << 20) - 1);
}

int genKey(int nodeIdx, int prevNodesIdx) {
    return nodeIdx << 20 | prevNodesIdx;
}

std::pair<int, vector<int> > optimal_path(const Matrix& graph) {
    size_t n = graph.size();
    unordered_map<int, std::pair<int, vector<int> > > cache;  // use unordered_map to improve performance
    cache[genKey(0, 1)] = std::make_pair(0, vector<int>{0});
    for(int s = 1; s < n; s++) { // i is the number of elements in the array (except starting point)
        unordered_map<int, std::pair<int, vector<int> > > newCache;
        for(int j = 1; j < n; j++) {
            int keyExist = 1 << j;
            for (auto& kv : cache) {
                int lastNodeIdx = getLastNodeIdx(kv.first);
                if (lastNodeIdx == j) continue;
                int nodesBinaryIdx = getNodesIdx(kv.first) | keyExist; // get the new key
		        if (nodesBinaryIdx == getNodesIdx(kv.first) || graph[lastNodeIdx][j] == INF) continue; // already in path or infinity
                auto key = genKey(j, nodesBinaryIdx);
                int sum = kv.second.first + graph[lastNodeIdx][j];

                auto prevIt = newCache.find(key);
                if (prevIt!=newCache.end()) {
                    if (sum >= prevIt->second.first) continue; // new total is bigger than the old
                }

                auto newValSecond = kv.second.second;
                newValSecond.push_back(j);
                newCache[key] = std::make_pair(sum, newValSecond);
            }
        }
        cache = newCache; // update cache, all keys contain s+1 members
    }

    int totalDist = INF;
    int minKey;
    for(auto& kv : cache) {
        int lastNodeIdx = getLastNodeIdx(kv.first);
        if (graph[lastNodeIdx][0]==INF) continue;
        int total = kv.second.first + graph[lastNodeIdx][0];
        if (total >= totalDist) continue;
        minKey = kv.first;
        totalDist = total;
    }
    if (totalDist==INF) return std::make_pair(-1, vector<int>{});
    return std::make_pair(totalDist, cache[minKey].second);
}

void print_answer(const std::pair<int, vector<int> >& answer) {
    std::cout << answer.first << "\n";
    if (answer.first == -1)
        return;
    const vector<int>& path = answer.second;
    for (size_t i = 0; i < path.size(); ++i)
        std::cout << path[i] + 1 << " ";
    std::cout << "\n";
}

int main() {
    print_answer(optimal_path(read_data()));
    return 0;
}
