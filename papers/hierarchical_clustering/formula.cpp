#include<vector>
#include<limits>
#include<algorithm>

#include "formula.h"
#include "util.h"

using std::vector;


tuple<size_t, size_t, double> chooseNoop(const vector<vector<double> >& d, const vector<bool>& removed) {
    return tuple<size_t, size_t, double>(0,0,0.0);
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

// argmax find two points with largest distance
tuple<size_t, size_t, double> argmax(const vector<vector<double> >& d, const vector<bool>& removed) {
    size_t start = 0, end = 0;
    double distance = 0;
    size_t N = removed.size();
    for(size_t i = 0; i< N; i++) {
        if (removed[i]) continue;
        for (size_t j = i+1; j < N; j++) {
            if (removed[j]) continue;
            if (d[i][j] > distance) {
                start = i;
                end = j;
                distance = d[i][j];
            }
        }
    }
    return tuple<size_t, size_t, double>(start, end, distance);
}



// formulaNoop does nothing, but implements the declaration
double formulaNoop(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x) {
    return 0.0;
}

double single(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    double dab = d[a][b];
    double dax = std::numeric_limits<double>::max(), dbx = std::numeric_limits<double>::max();
    vector<size_t> flattenedA = flatten(S, sizes, a);
    vector<size_t> flattenedB = flatten(S, sizes, b);
    vector<size_t> flattenedX = flatten(S, sizes, x);
    for(auto itx = flattenedX.begin(); itx < flattenedX.end(); itx++ ){
        for(auto ita = flattenedA.begin(); ita < flattenedA.end(); ita++) {
            if (dax > d[*ita][*itx]) dax = d[*ita][*itx];
        }
        for(auto itb = flattenedB.begin(); itb < flattenedB.end(); itb++) {
            if (dbx > d[*itb][*itx]) dbx = d[*itb][*itx];
        }
    }
    return std::min(dax, dbx);
}

double complete(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    double dab = d[a][b];
    double dax = 0, dbx = 0;
    vector<size_t> flattenedA = flatten(S, sizes, a);
    vector<size_t> flattenedB = flatten(S, sizes, b);
    vector<size_t> flattenedX = flatten(S, sizes, x);
    for(auto itx = flattenedX.begin(); itx < flattenedX.end(); itx++ ){
        for(auto ita = flattenedA.begin(); ita < flattenedA.end(); ita++) {
            if (dax < d[*ita][*itx]) dax = d[*ita][*itx];
        }
        for(auto itb = flattenedB.begin(); itb < flattenedB.end(); itb++) {
            if (dbx < d[*itb][*itx]) dbx = d[*itb][*itx];
        }
    }
    return std::max(dax, dbx);
}

double average(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    return 0.0;
}

double weighted(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    return 0.0;
}

double ward(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    return 0.0;
}

double centroid(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    return 0.0;
}

double median(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x){
    return 0.0;
}