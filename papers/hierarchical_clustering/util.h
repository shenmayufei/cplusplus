#ifndef UTIL_H_
#define UTIL_H_

#include<iostream>
#include<vector>
#include<tuple>

using std::tuple;
using std::vector;

vector<size_t> flatten(const vector<vector<size_t> >& S,  const vector<size_t>& sizes, size_t idx);

double calcDistance(const vector<double>& a, const vector<double>& b);

#endif
