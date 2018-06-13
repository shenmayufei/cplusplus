#ifndef FORMULA_H
#define FORMULA_H

#include<iostream>
#include<vector>

using std::vector;
using std::tuple;

typedef tuple<size_t, size_t, double> (*ChooseFunc)(const vector<vector<double> >& d, const vector<bool>& removed);
tuple<size_t, size_t, double> chooseNoop(const vector<vector<double> >& d, const vector<bool>& removed);
tuple<size_t, size_t, double> argmin(const vector<vector<double> >& d, const vector<bool>& removed);
tuple<size_t, size_t, double> argmax(const vector<vector<double> >& d, const vector<bool>& removed);


typedef double (*FormulaFunc)(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);

double formulaNoop(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);

double single(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double complete(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double average(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double weighted(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double ward(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double centroid(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
double median(const vector<vector<size_t> >& S, const vector<vector<double> >& d, const vector<size_t>& sizes, size_t a, size_t b, size_t x);
#endif