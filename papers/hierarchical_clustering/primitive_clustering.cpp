#include<iostream>
#include<vector>
#include<tuple>
#include<limits>
#include<cassert>
#include<string>
#include<cmath>
#include "util.h"
#include "formula.h"

using std::string;
using std::vector;
using std::tuple;
using std::pair;

vector<tuple<size_t,size_t,double> > primitive_clustering(const vector<vector<double> >& points, ChooseFunc chooseFunc,  FormulaFunc formulaFunc) {
    size_t N = points.size();
    vector<vector<double> > d (2*N, vector<double>(2*N, std::numeric_limits<double>::max()));
    for(size_t i = 0; i < N-1; i++) {
        for(size_t j = i+1; j < N; j++) {
            d[i][j] = calcDistance(points[i], points[j]);
            d[j][i] = d[i][j]; 
        }
    }

    vector<vector<size_t> > S(N, vector<size_t>());
    for(size_t i = 0; i < N; i++) S[i].push_back(i); // initialize labels
    vector<bool> removed(N, false);

    vector<tuple<size_t,size_t,double> > L;
    vector<size_t> sizes(N, 1);
    for(size_t i = 0; i < N-1; i++) {
        tuple<size_t, size_t, double> chosenRec = chooseFunc(d, removed); // step 6
        size_t a = std::get<0>(chosenRec);
        size_t b = std::get<1>(chosenRec);
        double distance = std::get<2>(chosenRec);
        if (a==0 && b==0) {
            break;
        }
        L.push_back(chosenRec); // step 7
        removed[a] = true; // step 8
        removed[b] = true; // step 8
        size_t newNodeIdx = S.size(); // step 9

        // update distance matrix for all other nodes
        for (size_t j = 0; j < newNodeIdx; j++) {
            if (removed[j]) continue;
            d[newNodeIdx][j] = d[j][newNodeIdx] = formulaFunc(S, d, sizes, a, b, j);
            // std::cout << "j=" << j << ", new node=" << newNodeIdx << ", dis=" << d[newNodeIdx][j] << std::endl;
        }
        sizes.push_back(sizes[a]+sizes[b]); // step 11
        S.push_back(vector<size_t>{a, b}); // step 12
        removed.push_back(false);
    }
    return L;
}

int main() {
    vector<vector<double> > S = {
        {1.0, 2.0},
        {3.0, 4.0},
        {6.0, 8.0},
        {50, 60},
        {100.0,100.0},
    };
    
    vector<tuple<size_t,size_t,double> > L = primitive_clustering(S, argmin, single);
    for (auto it = L.begin(); it < L.end(); it++) {
        std::cout << "<" << std::get<0>(*it) << ", " << std::get<1>(*it) << "> ==> " << std::get<2>(*it) << std::endl;
    }
    std::cout << "L size: " << L.size() << std::endl;

    L = primitive_clustering(S, argmax, complete);
    for (auto it = L.begin(); it < L.end(); it++) {
        std::cout << "<" << std::get<0>(*it) << ", " << std::get<1>(*it) << "> ==> " << std::get<2>(*it) << std::endl;
    }
    std::cout << "L size: " << L.size() << std::endl;
}