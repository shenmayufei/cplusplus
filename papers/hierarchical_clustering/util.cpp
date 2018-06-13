#include<vector>
#include "util.h"

using std::vector;

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
