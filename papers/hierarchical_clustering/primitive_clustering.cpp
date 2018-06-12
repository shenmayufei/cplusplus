#include<iostream>
#include<vector>
#include<tuple>

using std::vector;
using std::tuple;

vector<tuple<size_t,size_t,double>> primitive_clustering(vector<vector<double>>& S, vector<vector<double>>& distances) {
    size_t N = S.size();
    vector<tuple<size_t,size_t,double>> L;
    vector<size_t> sizes(N, 1);
    for(auto iter = sizes.begin(); iter != sizes.end(); iter++) {
        std::cout << "iter: " << *iter << std::endl;
    }
    return L;
}

int main() {
    vector<vector<double>> S = {
        {1.0, 2.0},
        {3.0, 4.0},
    };
    size_t N = S.size();
    vector<vector<double>> d (2*N, vector<double>(2*N));
    for(size_t i = 0; i < N-1; i++) {
        
    }
    
    auto L = primitive_clustering(S, d);
    std::cout << "L size: " << L.size() << std::endl;
}