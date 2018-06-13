#include<iostream>
#include<vector>
#include<tuple>
#include<limits>
#include<cassert>
#include<cmath>
#include "util.h"
#include "formula.h"

using std::vector;
using std::tuple;
using std::pair;

// calcDistance returns the distance of two points in N dimensional space
// two input points must have the same dimension
double calcDistance(const vector<double>& a, const vector<double>& b) {
    assert(a.size() == b.size());
    double sum = 0.0;
    for (size_t i = 0; i < a.size(); i++) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

// argmin find two points with smallest distance
tuple<size_t, size_t, double> argmin(const vector<vector<double> >& d, const vector<bool>& removed) {
    size_t start = 0, end = 0;
    double distance = std::numeric_limits<double>::max();
    size_t N = removed.size();
    for(size_t i = 0; i< N; i++) {
        if (removed[i]) continue;
        for (size_t j = i+1; j < N; j++) {
            if (removed[j]) continue;
            if (d[i][j] < distance) {
                start = i;
                end = j;
                distance = d[i][j];
            }
        }
    }
    return tuple<size_t, size_t, double>(start, end, distance);
}

vector<tuple<size_t,size_t,double> > primitive_clustering(const vector<vector<double> >& points) {
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
        tuple<size_t, size_t, double> minRec = argmin(d, removed); // step 6
        size_t a = std::get<0>(minRec);
        size_t b = std::get<1>(minRec);
        double distance = std::get<2>(minRec);
        if (a==0 && b==0) {
            break;
        }
        L.push_back(minRec); // step 7
        removed[a] = true; // step 8
        removed[b] = true; // step 8
        size_t newNodeIdx = S.size(); // step 9

        // update distance matrix for all other nodes
        for (size_t j = 0; j < newNodeIdx; j++) {
            if (removed[j]) continue;
            d[newNodeIdx][j] = d[j][newNodeIdx] = single(S, d, sizes, a, b, j);
            // std::cout << "j=" << j << ", new node=" << newNodeIdx << ", dis=" << d[newNodeIdx][j] << std::endl;
        }
        sizes.push_back(sizes[a]+sizes[b]); // step 11
        vector<size_t> members(S[a].begin(), S[a].end()); // step 12 -- start
        for(auto it = S[b].begin(); it < S[b].end(); it++) members.push_back(*it);
        S.push_back(members); // step 12 -- end
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
    
    vector<tuple<size_t,size_t,double> > L = primitive_clustering(S);
    for (auto it = L.begin(); it < L.end(); it++) {
        std::cout << "<" << std::get<0>(*it) << ", " << std::get<1>(*it) << "> ==> " << std::get<2>(*it) << std::endl;
    }
    std::cout << "L size: " << L.size() << std::endl;
}