#include <iostream>
#include <vector>

struct Vertex {
    int weight;
    std::vector <int> children;
};
typedef std::vector<Vertex> Graph;
typedef std::vector<int> Sum;

Graph ReadTree() {
    int vertices_count;
    std::cin >> vertices_count;

    Graph tree(vertices_count);

    for (int i = 0; i < vertices_count; ++i)
        std::cin >> tree[i].weight;

    for (int i = 1; i < vertices_count; ++i) {
        int from, to, weight;
        std::cin >> from >> to;
        tree[from - 1].children.push_back(to - 1);
        tree[to - 1].children.push_back(from - 1);
    }

    return tree;
}

void dfs(const Graph &tree, int vertex, std::vector<std::vector<int> >& cache, std::vector<bool>& visited) {
    if (visited[vertex]) return;
    visited[vertex] = true;
    cache[vertex][1] = tree[vertex].weight;
    if (tree[vertex].children.size() == 0) {
        return;
    }
    for(int child : tree[vertex].children) {
        dfs(tree, child, cache, visited);
        cache[vertex][0] += std::max(cache[child][0], cache[child][1]);
        cache[vertex][1] += cache[child][0];
    }
}

int MaxWeightIndependentTreeSubset(const Graph &tree) {
    size_t size = tree.size();
    if (size == 0)
        return 0;
    std::vector<std::vector<int> > cache(size, std::vector<int>(2, 0));
    std::vector<bool> visited(size, false);
    for(int v = 0; v < size; v++) dfs(tree, v, cache, visited);
    int max = 0;
    for(auto& vec : cache) {
        max = std::max(max, std::max(vec[0], vec[1]));
    }
    return max;
}

int main() {
    // This code is here to increase the stack size to avoid stack overflow
    // in depth-first search.
    // const rlim_t kStackSize = 64L * 1024L * 1024L;  // min stack size = 64 Mb
    // struct rlimit rl;
    // int result;
    // result = getrlimit(RLIMIT_STACK, &rl);
    // if (result == 0)
    // {
    //     if (rl.rlim_cur < kStackSize)
    //     {
    //         rl.rlim_cur = kStackSize;
    //         result = setrlimit(RLIMIT_STACK, &rl);
    //         if (result != 0)
    //         {
    //             fprintf(stderr, "setrlimit returned result = %d\n", result);
    //         }
    //     }
    // }

    // Here begins the solution
    Graph tree = ReadTree();
    int weight = MaxWeightIndependentTreeSubset(tree);
    std::cout << weight << std::endl;
    return 0;
}
