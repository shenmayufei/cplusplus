#include<vector>
#include<iostream>
#include<tuple>
#include<limits>
#include<cassert>
#include<cmath>
#include "util.h"

using std::vector;
using std::tuple;

vector<size_t> flatten(const vector<vector<size_t> >& S, const vector<size_t>& sizes, size_t idx) {
    vector<size_t> result;
    if (sizes[idx] <= 1) {
        return S[idx];
    }
    auto root = S[idx];
    for (vector<size_t>::const_iterator it = root.begin(); it < root.end(); it++){
        auto tmpVec = flatten(S, sizes, *it);
        for(vector<size_t>::const_iterator tmpIt = tmpVec.begin(); tmpIt < tmpVec.end(); tmpIt ++) 
            result.push_back(*tmpIt);
    }
    return result;
}


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
